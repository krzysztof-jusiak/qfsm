//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_ONACTION_HPP
#define QFSM_BACK_DETAIL_ONACTION_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include "QFsm/Back/Aux/Detail/Trace.hpp"
#include "QFsm/Back/Aux/TransitionTypes.hpp"
#include "QFsm/Back/Aux/Contains.hpp"
#include "QFsm/Back/Aux/State.hpp"
#include "QFsm/Back/Detail/OrthogonalRegions.hpp"
#include "QFsm/Front/Operations/None.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{

template<typename TFsmBase, typename TAction>
class OnAction
{
    typedef typename OrthogonalRegions<typename TFsmBase::Derived>::template ForEachRegion<> ForEachRegion;

    template<typename FsmBase, typename Enable = void> class ActionImpl
    {
    public:
        template<typename> static void execute(FsmBase&) { }
        static void execute(FsmBase&, typename FsmBase::State&) { }
    };

    template<typename FsmBase>
    class ActionImpl
    <
        FsmBase, typename boost::enable_if
        <
            boost::mpl::and_
            <
                Aux::Contains<typename FsmBase::Derived, Aux::Event, TAction>,
                boost::mpl::not_< Aux::Contains<typename FsmBase::Derived, Aux::TargetState, Front::Operations::None> >
            >
        >::type
    >
    {
    public:
        template<typename Region> static void execute(FsmBase& p_fsm)
        {
            execute(p_fsm, p_fsm.currentStates[Region::value]);
        }

        static void execute(FsmBase& p_fsm, typename FsmBase::State& p_state)
        {
            static_cast<typename FsmBase::Fsm&>(p_fsm).onAction(p_state, TAction());
        }
    };

    template<typename FsmBase>
    class ActionImpl
    <
        FsmBase, typename boost::enable_if
        <
            boost::mpl::and_
            <
                Aux::Contains<typename FsmBase::Derived, Aux::Event, TAction>,
                Aux::Contains<typename FsmBase::Derived, Aux::TargetState, Front::Operations::None>
            >
        >::type
    >
    {
    public:
        template<typename Region> static void execute(FsmBase& p_fsm)
        {
            execute(p_fsm, p_fsm.currentStates[Region::value]);
        }

        static void execute(FsmBase& p_fsm, typename FsmBase::State& p_state)
        {
            if (Aux::State<typename FsmBase::State, typename FsmBase::Fsm>::template equals<Front::Operations::None>(p_state))
            {
                static_cast<typename FsmBase::Fsm&>(p_fsm).onAction(p_state, TAction());
            }
        }
    };

public:
    static void execute(TFsmBase& p_fsm, typename TFsmBase::State& p_state)
    {
        ActionImpl<TFsmBase>::execute(p_fsm, p_state);
    }

    static void execute(TFsmBase& p_fsm)
    {
        ForEachRegion::template execute< ActionImpl<TFsmBase> >(p_fsm);
    }
};

} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

