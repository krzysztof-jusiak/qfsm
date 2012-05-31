//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_LOGGER_HPP
#define QFSM_BACK_LOGGER_HPP

#include <typeinfo>
#include <boost/shared_ptr.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/or.hpp>
#include "QFsm/Front/Operations/OnEntry.hpp"
#include "QFsm/Front/Operations/OnExit.hpp"

#ifndef QFSM_DEFAULT_LOGGER
# define QFSM_DEFAULT_LOGGER ::QFsm::Back::LoggerDisabled
#endif

namespace QFsm
{
namespace Back
{

class LoggerDisabled { };

template<typename TLogger>
class Logger
{
public:
    template<typename State, typename Pool> static void onEntryAction(Pool& p_pool)
    {
        logger(p_pool).onEntryAction(typeid(State));
    }

    template<typename Pool> static void onEntryAction(Pool& p_pool, const std::type_info& p_state)
    {
        logger(p_pool).onEntryAction(p_state);
    }

    template<typename State, typename Pool> static void onExitAction(Pool& p_pool)
    {
        logger(p_pool).onExitAction(typeid(State));
    }

    template<typename Pool> static void onExitAction(Pool& p_pool, const std::type_info& p_state)
    {
        logger(p_pool).onExitAction(p_state);
    }

    template<typename Event, typename Pool> static void onEventReceived(Pool& p_pool)
    {
        logger(p_pool).onEventReceived(typeid(Event));
    }

    template<typename Event, typename Pool> static void onUnexpectedEventReceived(Pool& p_pool)
    {
        logger(p_pool).onUnexpectedEventReceived(typeid(Event));
    }

    template<typename StateInit, typename StateTarget, typename Pool> static void onStateTransition(Pool& p_pool)
    {
        logger(p_pool).onStateTransition(typeid(StateInit), typeid(StateTarget));
    }

    template<typename Pool> static void onStateTransition(Pool& p_pool, const std::type_info& p_stateInit, const std::type_info& p_stateTarget)
    {
        logger(p_pool).onStateTransition(p_stateInit, p_stateTarget);
    }

    template<typename Guard, typename Pool> static void onGuardExecuted(Pool& p_pool)
    {
        logger(p_pool).onGuardExecuted(typeid(Guard));
    }

    template<typename Action, typename Pool> static void onActionExecuted(Pool& p_pool)
    {
        logger(p_pool).onActionExecuted(typeid(Action));
    }

    template<typename Event, typename State, typename Pool> static void onEvent(Pool& p_pool, typename boost::enable_if<boost::is_same<Front::Operations::OnEntry, Event> >::type* = 0)
    {
        logger(p_pool).onEntryAction(typeid(State));
    }

    template<typename Event, typename State, typename Pool> static void onEvent(Pool& p_pool, typename boost::enable_if<boost::is_same<Front::Operations::OnExit, Event> >::type* = 0)
    {
        logger(p_pool).onExitAction(typeid(State));
    }

    template<typename Event, typename State, typename Pool> static void onEvent(
        Pool&, typename boost::disable_if<boost::mpl::or_< boost::is_same<Front::Operations::OnEntry, Event>, boost::is_same<Front::Operations::OnExit, Event> > >::type* = 0)
    { }

private:
    template<typename Pool> static TLogger& logger(Pool& p_pool)
    {
        return p_pool.template acquire<TLogger>();
    }
};

template<>
class Logger<LoggerDisabled>
{
public:
    template<typename State, typename Pool> static void onEntryAction(Pool&) { }
    template<typename Pool> static void onEntryAction(Pool&, const std::type_info&) { }
    template<typename State, typename Pool> static void onExitAction(Pool&) { }
    template<typename Pool> static void onExitAction(Pool&, const std::type_info&) { }
    template<typename Event, typename Pool> static void onEventReceived(Pool&) { }
    template<typename Event, typename Pool> static void onUnexpectedEventReceived(Pool&) { }
    template<typename StateInit, typename StateTarget, typename Pool> static void onStateTransition(Pool&) { }
    template<typename Pool> static void onStateTransition(Pool&, const std::type_info&, const std::type_info&) { }
    template<typename Guard, typename Pool> static void onGuardExecuted(Pool&) { }
    template<typename Action, typename Pool> static void onActionExecuted(Pool&) { }
    template<typename Event, typename State, typename Pool> static void onEvent(Pool&) { }
};

} // namespace Back
} // namespace QFsm

#endif

