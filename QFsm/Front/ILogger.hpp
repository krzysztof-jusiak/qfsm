//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_ILOGGER_HPP
#define QFSM_FRONT_ILOGGER_HPP

#include <typeinfo>

namespace QFsm
{
namespace Front
{

/**
 * [Not mandatory] Logger interface
 */
class ILogger
{
public:
    virtual ~ILogger() { }
    virtual void onEntryAction(const std::type_info&) = 0;
    virtual void onExitAction(const std::type_info&) = 0;
    virtual void onEventReceived(const std::type_info&) = 0;
    virtual void onUnexpectedEventReceived(const std::type_info&) = 0;
    virtual void onStateTransition(const std::type_info&, const std::type_info&) = 0;
    virtual void onGuardExecuted(const std::type_info&) = 0;
    virtual void onActionExecuted(const std::type_info&) = 0;
};

} // namespace Front
} // namespace QFsm

#endif

