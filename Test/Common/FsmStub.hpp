//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_TEST_COMMON_FSMSTUB_HPP
#define QFSM_TEST_COMMON_FSMSTUB_HPP

#include <gtest/gtest.h>
#include <typeinfo>
#include <vector>
#include <cstring>
#include <boost/variant.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/push_back.hpp>
#include "QFsm/Back/Aux/FsmType.hpp"
#include "QFsm/Back/Aux/States.hpp"
#include "QFsm/Back/Aux/TransitionTypes.hpp"
#include "QFsm/Back/Logger.hpp"
#include "QFsm/Front/Operations/Transition.hpp"
#include "QFsm/Front/Operations/None.hpp"
#include "Common/PoolStub.hpp"
#include "Common/CacheStub.hpp"
#include "Common/DeferralEventStub.hpp"
#include "Common/InternalEventStub.hpp"

namespace QFsm
{

using Front::Operations::Transition;
using Front::Operations::_;

namespace Back
{
namespace Aux
{

template<typename, typename> class State;

template<typename TFsm>
class State<unsigned, TFsm>
{
public:
    static void init(unsigned& p_state, const boost::mpl::int_<0>&)
    {
        p_state = boost::mpl::find<typename TFsm::States, typename TFsm::InitialState>::type::pos::value;
    }

    template<int region> static void init(unsigned& p_state, const boost::mpl::int_<region>&)
    {
        typedef typename boost::mpl::at_c<typename TFsm::InitialState, region - 1>::type state;
        p_state = boost::mpl::find<typename TFsm::States, state>::type::pos::value;
    }

    template<typename TState> static bool equals(const unsigned& p_state)
    {
        return static_cast<unsigned>(boost::mpl::find<typename TFsm::States, TState>::type::pos::value) == p_state;
    }
};

} // namespace Aux
} // namespace Back

namespace Test
{
namespace Common
{

template<typename TTransitionTable = boost::mpl::vector< Transition<_, _, _> >, typename TInitialState = boost::mpl::_1, bool Result = true>
class FsmStub : Back::Aux::FsmType
{
    typedef typename Back::Aux::InitState<typename boost::mpl::begin<TTransitionTable>::type::type>::type InitState;
    typedef typename Back::Aux::Action<typename boost::mpl::begin<TTransitionTable>::type::type>::type Action;
    typedef typename Back::Aux::Guard<typename boost::mpl::begin<TTransitionTable>::type::type>::type Guard;

public:
    struct Derived
    {
        typedef TTransitionTable TransitionTable;
        typedef TInitialState InitialState;
        typedef typename Back::Aux::States<TTransitionTable>::type States;
    };

    struct Events : boost::mpl::fold
        <
            TTransitionTable,
            boost::mpl::vector0<>,
            boost::mpl::push_back< boost::mpl::_1, Back::Aux::Event<boost::mpl::_2> >
        >::type
    { };

    struct Policy
    {
        typedef void Orthogonality;
        typedef void Cache;
    };

    typedef Derived Fsm;
    typedef unsigned State;
    typedef typename Derived::States States;
    typedef Back::Logger<Back::LoggerDisabled> Log;
    typedef std::vector<typename boost::make_variant_over<Events>::type> ProcessEventCalls;
    typedef PoolStub<InitState, Guard, Action> Pool;

    FsmStub()
    {
        std::memset(&currentStates, 0, sizeof(currentStates));
    }

    template<typename T> bool processEvent(const T& p_event)
    {
        return processEvent_(p_event);
    }

    template<typename T> bool processEvent_(const T& p_event, typename boost::enable_if< boost::mpl::contains<Events, T> >::type* = 0)
    {
        ProcessEventCalls& l_processEventCalls = processEventCalls();
        l_processEventCalls.push_back(p_event);
        return Result;
    }

    template<typename T> bool processEvent_(const T&, typename boost::disable_if< boost::mpl::contains<Events, T> >::type* = 0)
    {
        return false;
    }

    static ProcessEventCalls& processEventCalls()
    {
        static ProcessEventCalls s_processEventCalls;
        return s_processEventCalls;
    }

    template<typename T> bool processEventImpl(const T& p_event)
    {
        return processEventImpl_(p_event);
    }

    template<typename T> bool processEventImpl_(const T& p_event, typename boost::enable_if< boost::mpl::contains<Events, T> >::type* = 0)
    {
        ProcessEventCalls& l_processEventImplCalls = processEventImplCalls();
        l_processEventImplCalls.push_back(p_event);
        return Result;
    }

    template<typename T> bool processEventImpl_(const T&, typename boost::disable_if< boost::mpl::contains<Events, T> >::type* = 0)
    {
        return false;
    }

    static ProcessEventCalls& processEventImplCalls()
    {
        static ProcessEventCalls s_processEventImplCalls;
        return s_processEventImplCalls;
    }

    Pool pool;
    CacheStub cache;
    DeferralEventStub deferralEvents;
    InternalEventStub internalEvents;
    State currentStates[boost::mpl::size<States>::value];
};

template<typename Fsm>
class VerifyTypes
{
    template<typename Expected>
    class VerifyVisitor : public boost::static_visitor<bool>
    {
    public:
        template<typename T> bool operator()(const T&) const
        {
            bool l_result = boost::is_same<Expected, T>::value;
            EXPECT_TRUE(l_result) << "expected: " << typeid(Expected).name() << ", given: " << typeid(T).name();
            return l_result;
        }
    };

public:
    explicit VerifyTypes(typename Fsm::ProcessEventCalls& p_calls)
        : index(1), m_calls(p_calls)
    { }

    template<typename T> void operator()(const T&)
    {
        boost::apply_visitor(VerifyVisitor<T>(), m_calls[index - 1]);
        ++index;
    }

private:
    unsigned index;
    typename Fsm::ProcessEventCalls& m_calls;
};

template<typename Expected, typename Fsm> void verifyProcessEvent()
{
    BOOST_MPL_ASSERT((boost::mpl::is_sequence<Expected>));
    ASSERT_EQ(std::size_t(boost::mpl::size<Expected>::value), Fsm::processEventCalls().size());
    boost::mpl::for_each<Expected>(VerifyTypes<Fsm>(Fsm::processEventCalls()));
    Fsm::processEventCalls().clear();
}

template<typename Expected, typename Fsm> void verifyProcessEventImpl()
{
    BOOST_MPL_ASSERT((boost::mpl::is_sequence<Expected>));
    ASSERT_EQ(std::size_t(boost::mpl::size<Expected>::value), Fsm::processEventImplCalls().size());
    boost::mpl::for_each<Expected>(VerifyTypes<Fsm>(Fsm::processEventImplCalls()));
    Fsm::processEventImplCalls().clear();
}

} // namespace Common
} // namespace Test
} // namespace QFsm

#endif

