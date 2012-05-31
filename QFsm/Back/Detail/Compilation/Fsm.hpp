//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_COMPILATION_FSM_HPP
#define QFSM_BACK_DETAIL_COMPILATION_FSM_HPP

#include <boost/mpl/vector.hpp>
#include "QFsm/Front/Operations/OnEntry.hpp"
#include "QFsm/Front/Operations/OnExit.hpp"
#include "QFsm/Back/Detail/Compilation/DispatchEvent.hpp"
#include "QFsm/Back/Detail/Compilation/State.hpp"
#include "QFsm/Back/FsmBase.hpp"
#include "QFsm/Back/Aux/Detail/Ctor.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{
namespace Compilation
{

template
<
    typename TDerived,
    typename TPool
>
class Fsm : public FsmBase<Fsm<TDerived, TPool>, TDerived, TPool, State>
{
    typedef FsmBase<Fsm, TDerived, TPool, State> Base;

public:
    CTOR_REF(Fsm, Base, { })

    template<typename Event> bool handleEvent(const Event& p_event, const State& p_currentState, State& p_newState)
    {
        return dispatchEvent<Event, Base, typename Base::TransitionTable, typename Base::States>(
            p_currentState, p_newState, p_event, *this);
    }

    void onAction(const State& p_state, const Front::Operations::OnEntry&)
    {
        State l_newState; // not used
        dispatchEvent<Front::Operations::OnEntry, Base, typename Base::TransitionTable, typename Base::States>(
            p_state, l_newState, Front::Operations::OnEntry(), *this);
    }

    void onAction(const State& p_state, const Front::Operations::OnExit&)
    {
        State l_newState; // not used
        dispatchEvent<Front::Operations::OnExit, Base, typename Base::TransitionTable, typename Base::States>(
            p_state, l_newState, Front::Operations::OnExit(), *this);
    }
};

} // namespace Compilation
} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

