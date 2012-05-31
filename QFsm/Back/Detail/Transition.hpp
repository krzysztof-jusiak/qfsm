//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_TRANSITION_HPP
#define QFSM_BACK_DETAIL_TRANSITION_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include "QFsm/Back/Aux/TransitionTypes.hpp"
#include "QFsm/Back/Aux/Contains.hpp"
#include "QFsm/Front/Operations/None.hpp"
#include "QFsm/Back/Aux/Extensions.hpp"

#if defined(QFSM_EXTENSIONS_UML)
# include "QFsm/Back/Detail/OnAction.hpp"
#endif

namespace QFsm
{
namespace Back
{
namespace Detail
{

template<typename TFsmBase, typename Enable = void>
class Transition
{
public:
    static void execute(TFsmBase& QFSM_UML_EXTENSIONS(p_fsm), typename TFsmBase::State& p_currentState, const typename TFsmBase::State& p_newState)
    {
        QFSM_UML_EXTENSIONS(
            Detail::OnAction<TFsmBase, Front::Operations::OnExit>::execute(p_fsm, p_currentState);
        )

        p_currentState = p_newState;

        TRACE("transition");

        QFSM_UML_EXTENSIONS(
            Detail::OnAction<TFsmBase, Front::Operations::OnEntry>::execute(p_fsm, p_currentState);
        )
    }
};

template<typename TFsmBase>
class Transition<TFsmBase, typename boost::enable_if< Aux::Contains<typename TFsmBase::Derived, Aux::TargetState, Front::Operations::None> >::type>
{
public:
    static void execute(TFsmBase& QFSM_UML_EXTENSIONS(p_fsm), typename TFsmBase::State& p_currentState, const typename TFsmBase::State& p_newState)
    {
        if (!Aux::State<typename TFsmBase::State, typename TFsmBase::Fsm>::template equals<Front::Operations::None>(p_newState))
        {
            QFSM_UML_EXTENSIONS(
                Detail::OnAction<TFsmBase, Front::Operations::OnExit>::execute(p_fsm, p_currentState);
            )

            p_currentState = p_newState;

            TRACE("transition");

            QFSM_UML_EXTENSIONS(
                Detail::OnAction<TFsmBase, Front::Operations::OnEntry>::execute(p_fsm, p_currentState);
            )
        }
    }
};

} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

