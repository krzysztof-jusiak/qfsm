//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_AUX_SILENTLOGGER_HPP
#define QFSM_FRONT_AUX_SILENTLOGGER_HPP

#include <exception>
#include "QFsm/Back/Aux/Trace.hpp"
#include "QFsm/Front/CLogger.hpp"

namespace QFsm
{
namespace Front
{
namespace Aux
{

class SilentLogger : public QFsm::Front::CLogger<SilentLogger>
{
public:
    template<typename State> void onStateInit()
    {
        QFSM_TRACE("[%s]", typeid(State).name());
    }

    template<typename State> void onEntryAction()
    {
        QFSM_TRACE("[%s]", typeid(State).name());
    }

    template<typename State> void onExitAction()
    {
        QFSM_TRACE("[%s]", typeid(State).name());
    }

    template<typename Event> void onEventReceived(const Event&)
    {
        QFSM_TRACE("[%s]", typeid(Event).name());
    }

    template<typename Event, typename State> void onUnexpectedEventReceived(const Event&)
    {
        QFSM_TRACE("[%s] in [%s]", typeid(Event).name(), typeid(State).name());
    }

    template<typename T> void onExceptionCaught(const std::exception& QFSM_UNUSED(p_exception))
    {
        QFSM_TRACE("[%s] : %s", typeid(T).name(), p_exception.what());
    }

    template<typename SourceState, typename TargetState> void onStateTransition()
    {
        QFSM_TRACE("[%s] -> [%s]", typeid(SourceState).name(), typeid(TargetState).name());
    }

    template<typename Guard> void onGuardExecution()
    {
        QFSM_TRACE("[%s]", typeid(Guard).name());
    }

    template<typename Guard> void onGuardExecuted(bool QFSM_UNUSED(p_result))
    {
        QFSM_TRACE("[%s] : %s", typeid(Guard).name(), (p_result ? "OK" : "NotOK"));
    }

    template<typename Action, typename TResult> void onActionExecution()
    {
        QFSM_TRACE("[%s] returns %s", typeid(Action).name(), typeid(TResult).name());
    }
};

} // namespace Aux
} // namespace Front
} // namespace QFsm

#endif

