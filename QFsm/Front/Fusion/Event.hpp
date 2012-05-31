//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_FUSION_EVENT_HPP
#define QFSM_FRONT_FUSION_EVENT_HPP

#include <boost/shared_ptr.hpp>
#include "QFsm/Front/IAction.hpp"
#include "QFsm/Front/IGuard.hpp"

namespace QFsm
{
namespace Front
{
namespace Fusion
{

namespace Detail
{

template<typename TEvent>
class DummyGuard : public Front::Detail::IGuard<TEvent>
{
public:
    bool operator()(const TEvent&) { return true; }
};

template<typename TEvent>
class DummyAction : public Front::Detail::IAction<TEvent>
{
public:
    void operator()(const TEvent&) { }
};

} // namespace Detail

template<typename TEvent, bool = true>
class Event
{
    typedef boost::shared_ptr< Front::Detail::IAction<TEvent> > Action;
    typedef boost::shared_ptr< Front::Detail::IGuard<TEvent> > Guard;

public:
    typedef TEvent type;

    Event()
    {
        static Action s_dummyAction = Action(new Detail::DummyAction<TEvent>());
        m_action = s_dummyAction;

        static Guard s_dummyGuard = Guard(new Detail::DummyGuard<TEvent>());
        m_guard = s_dummyGuard;
    }

    explicit Event(const Guard& p_guard)
        : m_guard(p_guard)
    {
        static Action s_dummyAction = Action(new Detail::DummyAction<TEvent>());
        m_action = s_dummyAction;
    }

    Event<TEvent, false>& operator/(const Action& p_action)
    {
        m_action = p_action;
        return static_cast<Event<TEvent, false>&>(*this);
    }

    Action action() { return m_action; }
    Guard guard() { return m_guard; }

private:
    Action m_action;
    Guard m_guard;
};

template<typename TEvent> class Event<TEvent, false> :  Event<TEvent, true>
{
public:
    using Event<TEvent, true>::action;
    using Event<TEvent, true>::guard;
};

} // namespace Front
} // namespace Fusion
} // namespace QFsm

#endif

