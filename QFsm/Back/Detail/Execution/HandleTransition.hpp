//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_EXECUTION_HANDLETRANSITION_HPP
#define QFSM_BACK_DETAIL_EXECUTION_HANDLETRANSITION_HPP

#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/type_traits/is_same.hpp>
#include "QFsm/Back/Detail/Execution/State.hpp"
#include "QFsm/Back/Aux/FsmType.hpp"
#include "QFsm/Back/Aux/Call.hpp"
#include "QFsm/Back/Aux/Extensions.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{
namespace Execution
{

template<typename TStates, typename TEvent, typename TTransitions> class HandleTransition
{
    template<bool> struct IsLast { };

    template
    <
        typename Iterator,
        typename LastIterator,
        typename TFsm
    >
    static bool executeImpl(const TEvent& p_event,
                            State& p_newState,
                            TFsm& p_fsm,
                            const IsLast<false>&)
    {
        typedef typename boost::mpl::deref<Iterator>::type Current;
        typedef typename boost::mpl::next<Iterator>::type Next;
        typedef typename boost::mpl::find<TStates, typename Current::StateTarget>::type::pos StateTargetId;
        typedef IsLast<boost::is_same<Next, LastIterator>::value> IsLastType;

        TFsm::Log::template onEvent<TEvent, typename Current::StateInit>(p_fsm.pool);

        if (Aux::Call<bool, typename Current::Guard>::execute(p_event, p_fsm))
        {
            Aux::Call<void, typename Current::Action>::execute(p_event, p_fsm);
            p_newState = StateTargetId::value;
            TFsm::Log::template onStateTransition<typename Current::StateInit, typename Current::StateTarget>(p_fsm.pool);
            return true;
        }

        return executeImpl<Next, LastIterator>(p_event, p_newState, p_fsm, IsLastType());
    }

    template
    <
        typename Iterator,
        typename LastIterator,
        typename TFsm
    >
    static bool executeImpl(const TEvent&, State&, TFsm&, const IsLast<true>&)
    {
        return false;
    }

public:
    template<typename TFsm> static bool execute(const TEvent& p_event,
                                                State& p_newState,
                                                TFsm& p_fsm)
    {
        typedef typename boost::mpl::begin<TTransitions>::type First;
        typedef typename boost::mpl::end<TTransitions>::type Last;
        typedef IsLast<boost::is_same<First, Last>::value> IsLastType;

        return executeImpl<First, Last, TFsm>(p_event, p_newState, p_fsm, IsLastType());
    }
};

} // namespace Back
} // namespace Detail
} // namespace Execution
} // namespace QFsm

#endif

