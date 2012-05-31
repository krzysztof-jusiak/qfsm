//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_EXECUTION_DISPATCHTABLE_HPP
#define QFSM_BACK_DETAIL_EXECUTION_DISPATCHTABLE_HPP

#include <boost/mpl/map.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include "QFsm/Back/Aux/Detail/ForEach.hpp"
#include "QFsm/Back/Detail/Execution/State.hpp"
#include "QFsm/Back/Detail/Execution/HandleTransition.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{
namespace Execution
{

template<typename TTransitionTable, typename TStates, typename TEvent, typename TFsm>
class DispatchTable
{
    typedef bool (*cell)(const TEvent&, State&, TFsm&);

    class NoTransition
    {
    public:
        static bool execute(const TEvent&, State&, TFsm&) { return false; }
    };

    class InitDefault
    {
    public:
        explicit InitDefault(DispatchTable& p_self)
            : m_self(p_self)
        { }

        template<typename State> void operator()()
        {
            typedef typename boost::mpl::find<TStates, State>::type::pos StateId;
            m_self.entries[StateId::value] = &NoTransition::execute;
        }

    private:
        DispatchTable& m_self;
    };

    class Init
    {
    public:
        explicit Init(DispatchTable& p_self)
            : m_self(p_self)
        { }

        template<typename PairStateTransitions> void operator()()
        {
            typedef typename PairStateTransitions::first CurrentState;
            typedef typename PairStateTransitions::second CurrentStateTransitions;
            typedef typename boost::mpl::find<TStates, CurrentState>::type::pos StateInitId;

            m_self.entries[StateInitId::value] =
                &HandleTransition<TStates, TEvent, CurrentStateTransitions>::execute;
        }

    private:
        DispatchTable& m_self;
    };

    template<typename Transition, typename State> struct IsExpected : boost::mpl::and_
        <
            boost::is_base_of<typename Transition::Event, TEvent>, //event hierarchy
            boost::is_same<typename Transition::StateInit, State>
        >
    { };

    template<typename State> struct AddStateTransitions : boost::mpl::pair
        <
            State, boost::mpl::filter_view<TTransitionTable, IsExpected<boost::mpl::_1, State> >
        >
    { };

public:
    DispatchTable()
    {
        Aux::Detail::forEach<TStates>(InitDefault(*this));

        Aux::Detail::forEach
        <
            typename boost::mpl::transform
            <
                TStates,
                AddStateTransitions<boost::mpl::_1>,
                boost::mpl::back_inserter< boost::mpl::vector0<> >
            >::type
        >
        (Init(*this));
    }

    static const DispatchTable& instance()
    {
        static const DispatchTable s_instance;
        return s_instance;
    }

    cell entries[boost::mpl::size<TStates>::value];
};

} // namespace Back
} // namespace Detail
} // namespace Execution
} // namespace QFsm

#endif

