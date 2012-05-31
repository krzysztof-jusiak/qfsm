//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_INTERNALEVENT_HPP
#define QFSM_BACK_DETAIL_INTERNALEVENT_HPP

#include <deque>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/utility/enable_if.hpp>
#include "QFsm/Back/Aux/Contains.hpp"
#include "QFsm/Front/Operations/SendInternalEvent.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{

template<typename TFsmBase, typename Enable = void> class InternalEvent
{
public:
    void execute(bool) { }
};

template<typename TFsmBase>
class InternalEvent<TFsmBase, typename boost::enable_if< Aux::Contains<typename TFsmBase::Derived, Aux::Action, Front::Operations::SendInternalEvent_> >::type>
{
    typedef boost::function<void()> ExecuteEvent;

public:
    void execute(bool p_handled)
    {
        if (p_handled && !m_internalEvents.empty())
        {
            TRACE("handle internal event");
            ExecuteEvent l_executeEvent = m_internalEvents.front();
            m_internalEvents.pop_front();
            l_executeEvent();
        }
    }

    void addInternalEvent(const ExecuteEvent& p_event)
    {
        m_internalEvents.push_back(p_event);
    }

private:
    std::deque<ExecuteEvent> m_internalEvents;
};

} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

