//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_CLOGGER_HPP
#define QFSM_FRONT_CLOGGER_HPP

#include <exception>
#include "QFsm/Back/Aux/Concept.hpp"
#include "QFsm/Back/Aux/Logger.hpp"

namespace QFsm
{
namespace Front
{

/**
 * Logger concept
 *
 * @code
 * class MyLogger : public QFsm::Front::CLogger<CLogger>
 * {
 * public:
 *      template<typename State> void onStateInit() { }
 *      template<typename State> void onEntryAction() { }
 *      template<typename State> void onExitAction() { }
 *      template<typename Event> void onEventReceived(const Event&) { }
 *      template<typename Event, typename State> void onUnexpectedEventReceived(const Event&) { }
 *      template<typename T> void onExceptionCaught(const std::exception&) { }
 *      template<typename SourceState, typename TargetState> void onStateTransition() { }
 *      template<typename T> void onGuardExecution() { }
 *      template<typename T> void onGuardExecuted(bool) { }
 *      template<typename T> void onActionExecution() { }
 * };
 * @endcode
 */
template<typename T>
class CLogger : public QFsm::Aux::Concept<T>, QFsm::Back::Aux::Logger
{
public:
    void conceptUsage()
    {
        //template<typename State> void onStateInit();
        static_cast<T*>(this)->template onStateInit< QFsm::Aux::AnyType<0> >();

        //template<typename State> void onEntryAction();
        static_cast<T*>(this)->template onEntryAction< QFsm::Aux::AnyType<0> >();

        //template<typename State> void onExitAction();
        static_cast<T*>(this)->template onExitAction< QFsm::Aux::AnyType<0> >();

        //template<typename Event> void onEventReceived(const Event&);
        static_cast<T*>(this)->template onEventReceived< QFsm::Aux::AnyType<0> >(QFsm::Aux::AnyType<0>());

        //template<typename Event, typename State> void onUnexpectedEventReceived(const Event&);
        static_cast<T*>(this)->template onUnexpectedEventReceived< QFsm::Aux::AnyType<0>, QFsm::Aux::AnyType<1> >(QFsm::Aux::AnyType<0>());

        //template<typename T> void onExceptionCaught(const std::exception&);
        static_cast<T*>(this)->template onExceptionCaught< QFsm::Aux::AnyType<0> >(std::exception());

        //template<typename SourceState, typename TargetState> void onStateTransition();
        static_cast<T*>(this)->template onStateTransition< QFsm::Aux::AnyType<0>, QFsm::Aux::AnyType<1> >();

        //template<typename T> void onGuardExecution();
        static_cast<T*>(this)->template onGuardExecution< QFsm::Aux::AnyType<0> >();

        //template<typename T> void onGuardExecuted(bool);
        static_cast<T*>(this)->template onGuardExecuted< QFsm::Aux::AnyType<0> >(false);

        //template<typename T> void onActionExecution();
        static_cast<T*>(this)->template onActionExecution< QFsm::Aux::AnyType<0> >();
    }
};

} // namespace Front
} // namespace QFsm

#endif

