//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_UNEXPECTEDEVENT_HPP
#define QFSM_BACK_DETAIL_UNEXPECTEDEVENT_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include "QFsm/Back/Aux/TransitionTypes.hpp"
#include "QFsm/Back/Aux/Contains.hpp"
#include "QFsm/Back/Detail/Visitor.hpp"
#include "QFsm/Front/Operations/None.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{

template<typename TFsmBase>
class UnexpectedEvent
{
    template<typename Event> class UnexpectedEventVisitor
    {
    public:
        UnexpectedEventVisitor(typename TFsmBase::Pool& p_pool, const Event& p_event)
            : m_pool(p_pool), m_event(p_event)
        { }

        template<typename State> void operator()() const
        {
            TRACE("unexpected event [%s]", typeid(Event).name());
            TFsmBase::Log::template onUnexpectedEventReceived<State>(m_pool);
            (m_pool.template acquire<typename TFsmBase::Derived::UnexpectedEvent>()).operator()<Event, State>(m_event);
        }

    private:
        typename TFsmBase::Pool& m_pool;
        const Event& m_event;
    };

public:
    template<typename Event> static bool execute(TFsmBase&, const Event&, bool p_isHandled, typename boost::enable_if< boost::is_base_of<Front::Operations::None, Event> >::type* = 0)
    {
        return p_isHandled;
    }

    template<typename Event> static bool execute(TFsmBase& p_fsm, const Event& p_event, bool p_isHandled, typename boost::disable_if< boost::is_base_of<Front::Operations::None, Event> >::type* = 0)
    {
        if (!p_isHandled)
        {
            UnexpectedEventVisitor<Event> l_visitor(p_fsm.pool, p_event);
            Detail::Visitor<TFsmBase>::execute(p_fsm, l_visitor);
        }

        return p_isHandled;
    }
};

} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

