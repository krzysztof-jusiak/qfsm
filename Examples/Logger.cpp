//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <QFsm/QFsm.hpp>
#include "Utility.hpp"

class Action
{
public:
    template<typename Event> void operator()(const Event&) { }
};

class Guard
{
public:
    template<typename Event> bool operator()(const Event&) { return true; }
};

class MyLogger : public QFsm::Front::ILogger
{
public:
    explicit MyLogger(const std::string& p_name)
        : m_name(p_name)
    { }

    void onEntryAction(const std::type_info& p_state)
    {
        std::cout << "[" << m_name << "] - entry action: " << printType(p_state) << std::endl;
    }

    void onExitAction(const std::type_info& p_state)
    {
        std::cout << "[" << m_name << "] - exit action: " << printType(p_state) << std::endl;
    }

    void onEventReceived(const std::type_info& p_event)
    {
        std::cout << "[" << m_name << "] - event received: " << printType(p_event) << std::endl;
    }

    void onUnexpectedEventReceived(const std::type_info& p_event)
    {
        std::cout << "[" << m_name << "] - unexpected event received: " << printType(p_event) << std::endl;
    }

    void onStateTransition(const std::type_info& p_oldState, const std::type_info& p_newState)
    {
        std::cout << "[" << m_name << "] - state transition: " << printType(p_oldState) << " -> " << printType(p_newState) << std::endl;
    }

    void onGuardExecuted(const std::type_info& p_guard)
    {
        std::cout << "[" << m_name << "] - guard executed: " << printType(p_guard) << std::endl;
    }

    void onActionExecuted(const std::type_info& p_action)
    {
        std::cout << "[" << m_name << "] - action executed: " << printType(p_action) << std::endl;
    }

private:
    std::string m_name;
};

class Logger_ : public QFsm::Fsm
{
    struct S1 { };
    struct S2 { };

public:
    typedef QFsm::TransitionTable
    <
        Transition < S1, e1, S2, Action, Guard >,
        Transition < S2, e2, S1, _, Guard >
    >
    TransitionTable;

    typedef MyLogger Logger;
};

int main()
{
    QFsm::Front::Fsm<Logger_> fsm(boost::make_shared<MyLogger>("MyLogger"));
    fsm.processEvent(e1());
    fsm.processEvent(e2());

    return 0;
}

