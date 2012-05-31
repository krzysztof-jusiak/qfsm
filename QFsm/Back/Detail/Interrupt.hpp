//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_INTERRUPT_HPP
#define QFSM_BACK_DETAIL_INTERRUPT_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include "QFsm/Back/Aux/TransitionTypes.hpp"
#include "QFsm/Back/Aux/Contains.hpp"
#include "QFsm/Back/Detail/Visitor.hpp"
#include "QFsm/Back/Detail/UnexpectedEvent.hpp"
#include "QFsm/Front/Operations/Interrupt.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{

template<typename TFsmBase, typename Enable = void> class Interrupt
{
public:
    template<typename Event> static bool execute(TFsmBase&, const Event&) { return true; }
};

template<typename TFsmBase>
class Interrupt<TFsmBase, typename boost::enable_if< Aux::Contains<typename TFsmBase::Derived, Aux::TargetState, Front::Operations::Interrupt_> >::type>
{

    template<typename Event> class IsInterruptedVisitor
    {
        template<bool> class IsInterrupted { };

    public:
        explicit IsInterruptedVisitor(bool& p_isInterrupted)
            : m_isInterrupted(p_isInterrupted)
        { }

        template<typename State> void operator()(typename boost::enable_if< boost::is_base_of<Front::Operations::Interrupt_, State> >::type* = 0) const
        {
            m_isInterrupted = m_isInterrupted || boost::is_base_of<Event, typename State::type>::value;
        }

        template<typename State> void operator()(typename boost::disable_if< boost::is_base_of<Front::Operations::Interrupt_, State> >::type* = 0) const
        { }

    private:
        bool& m_isInterrupted;
    };

public:
    template<typename Event> static bool execute(TFsmBase& p_fsm, const Event& p_event)
    {
        bool l_isInterrupted = false;

        //search if any state of all regions is in interrupted state
        IsInterruptedVisitor<Event> l_visitor(l_isInterrupted);
        Detail::Visitor<TFsmBase>(p_fsm, l_visitor);

        if (l_isInterrupted)
        {
            return UnexpectedEvent<TFsmBase>::execute(p_fsm, p_event, !l_isInterrupted);
        }

        return true;
    }
};

} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

