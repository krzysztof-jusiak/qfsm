//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_COMPILATION_DISPATCHEVENT_HPP
#define QFSM_BACK_DETAIL_COMPILATION_DISPATCHEVENT_HPP

#include <boost/mpl/vector.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include "QFsm/Front/Operations/None.hpp"
#include "QFsm/Back/Detail/Compilation/HandleTransition.hpp"
#include "QFsm/Back/Aux/FsmType.hpp"
#include "QFsm/Back/Aux/Extensions.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{
namespace Compilation
{
namespace Detail
{

template<bool> class IsLast { };

class DispatchEvent
{
public:
    template
    <
        typename TEvent,
        typename TFsm,
        typename TTransitionTable,
        typename TStates,
        typename TIterator,
        typename TLastIterator
    >
    static bool execute(const State& p_currentState, State& p_newState, const TEvent& p_event, TFsm& p_fsm, const IsLast<false>&)
    {
        typedef typename boost::mpl::deref<TIterator>::type Row;
        typedef typename boost::mpl::next<TIterator>::type NextIterator;
        typedef typename boost::mpl::find<TStates, typename Row::StateInit>::type::pos StateInitId;
        typedef typename boost::mpl::find<TStates, typename Row::StateTarget>::type::pos StateTargetId;
        typedef HandleTransition<StateInitId::value, typename Row::StateInit, typename Row::Event, typename Row::StateTarget, typename Row::Action, typename Row::Guard> Operation;

        bool l_handleEvent = Operation::execute(p_currentState, p_event, p_fsm);

        if (l_handleEvent)
        {
            TFsm::Log::template onStateTransition<typename Row::StateInit, typename Row::StateTarget>(p_fsm.pool);
            p_newState = State(StateTargetId::value);
            return l_handleEvent;
        }

        return execute<TEvent, TFsm, TTransitionTable, TStates, NextIterator, TLastIterator>(
            p_currentState, p_newState, p_event, p_fsm, IsLast<boost::is_same<NextIterator, TLastIterator>::value>());
    }

    template
    <
        typename TEvent,
        typename TFsm,
        typename TTransitionTable,
        typename TStates,
        typename TIterator,
        typename TLastIterator
    >
    static bool execute(const State&, State&, const TEvent&, TFsm&, const IsLast<true>&)
    {
        return false;
    }
};

} // namespace Detail

template
<
    typename TEvent,
    typename TFsm,
    typename TTransitionTable,
    typename TStates
>
bool dispatchEvent(const State& p_currentState, State& p_newState, const TEvent& p_event, TFsm& p_fsm)
{
    using namespace Detail;

    typedef typename boost::mpl::begin<TTransitionTable>::type l_first;
    typedef typename boost::mpl::end<TTransitionTable>::type l_last;

    return DispatchEvent::execute<TEvent, TFsm, TTransitionTable, TStates, l_first, l_last>(
        p_currentState, p_newState, p_event, p_fsm, IsLast<boost::is_same<l_first, l_last>::value>());
}

} // namespace Compilation
} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

