//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_EXECUTION_FSM_HPP
#define QFSM_BACK_DETAIL_EXECUTION_FSM_HPP

#include "QFsm/Front/Operations/OnEntry.hpp"
#include "QFsm/Front/Operations/OnExit.hpp"
#include "QFsm/Back/Detail/Execution/DispatchTable.hpp"
#include "QFsm/Back/Detail/Execution/State.hpp"
#include "QFsm/Back/FsmBase.hpp"
#include "QFsm/Back/Aux/Detail/Ctor.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{
namespace Execution
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
        typedef DispatchTable<typename TDerived::TransitionTable, typename Base::States, Event, Base> table;
        return table::instance().entries[p_currentState](p_event, p_newState, *this);
    }

    void onAction(const State& p_state, const Front::Operations::OnEntry&)
    {
        State l_newState; // not used
        typedef DispatchTable<typename TDerived::TransitionTable, typename Base::States, Front::Operations::OnEntry, Base> tableOnEntry;
        tableOnEntry::instance().entries[p_state](Front::Operations::OnExit(), l_newState, *this);
    }

    void onAction(const State& p_state, const Front::Operations::OnExit&)
    {
        State l_newState; // not used
        typedef DispatchTable<typename TDerived::TransitionTable, typename Base::States, Front::Operations::OnExit, Base> tableOnExit;
        tableOnExit::instance().entries[p_state](Front::Operations::OnEntry(), l_newState, *this);
    }
};

} // namespace Back
} // namespace Detail
} // namespace Execution
} // namespace QFsm

#endif

