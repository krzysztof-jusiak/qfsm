//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_DEFERRALEVENT_HPP
#define QFSM_BACK_DETAIL_DEFERRALEVENT_HPP

#include <deque>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/utility/enable_if.hpp>
#include "QFsm/Back/Aux/TransitionTypes.hpp"
#include "QFsm/Back/Aux/Contains.hpp"
#include "QFsm/Front/Operations/Defer.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{

template<typename TFsmBase, typename Enable = void> class DeferralEvent
{
public:
    void init() { }
    void execute(bool) { }
};

template<typename TFsmBase>
class DeferralEvent<TFsmBase, typename boost::enable_if< Aux::Contains<typename TFsmBase::Derived, Aux::Action, Front::Operations::Defer> >::type>
{
    typedef boost::function<void()> ExecuteEvent;

public:
    DeferralEvent()
        : m_queueSize(0)
    { }

    void init()
    {
        m_queueSize = m_deferralEvents.size();
    }

    void execute(bool p_handled)
    {
        if (p_handled && !m_deferralEvents.empty() && m_deferralEvents.size() == m_queueSize)
        {
            TRACE("handle deferral event");
            ExecuteEvent l_executeEvent = m_deferralEvents.front();
            m_deferralEvents.pop_front();
            l_executeEvent();
        }
    }

    void addDeferralEvent(const ExecuteEvent& p_event)
    {
        m_deferralEvents.push_back(p_event);
    }

private:
    std::deque<ExecuteEvent> m_deferralEvents;
    std::size_t m_queueSize;
};

} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

