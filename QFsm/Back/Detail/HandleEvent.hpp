//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_HANDLEEVENT_HPP
#define QFSM_BACK_DETAIL_HANDLEEVENT_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include "QFsm/Back/Aux/TransitionTypes.hpp"
#include "QFsm/Back/Aux/Contains.hpp"
#include "QFsm/Back/Aux/State.hpp"
#include "QFsm/Back/Aux/Detail/Trace.hpp"
#include "QFsm/Back/Detail/OrthogonalRegions.hpp"
#include "QFsm/Back/Detail/Transition.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{

template<typename TFsmBase>
class HandleEvent
{
    typedef typename OrthogonalRegions<typename TFsmBase::Derived>::template ForEachRegion<> ForEachRegion;

    class HandleEventImpl
    {
        static bool executeImpl(TFsmBase& p_fsm, bool p_handled, typename TFsmBase::State& p_currentState, const typename TFsmBase::State& p_newState)
        {
            TRACE("process: %d", p_handled);

            if (p_handled)
            {
                Detail::Transition<TFsmBase>::execute(p_fsm, p_currentState, p_newState);
                return true;
            }

            return false;
        }

    public:
        template<typename Region, typename Event> static void execute(TFsmBase& p_fsm, const Event& p_event, bool& p_handled)
        {
            TRACE("handle event [%s]", typeid(p_event).name());

            typename TFsmBase::State l_newState;
            bool l_handled = static_cast<typename TFsmBase::Fsm&>(p_fsm).handleEvent(p_event, p_fsm.currentStates[Region::value], l_newState);
            p_handled = executeImpl(p_fsm, l_handled, p_fsm.currentStates[Region::value], l_newState) || p_handled;
        }
    };

public:
    template<typename Event> static void execute(TFsmBase& p_fsm, const Event& p_event, bool& p_handled)
    {
        ForEachRegion::template execute<HandleEventImpl>(p_fsm, p_event, p_handled);
    }
};

} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

