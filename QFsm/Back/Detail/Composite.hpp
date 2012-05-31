//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_COMPOSITE_HPP
#define QFSM_BACK_DETAIL_COMPOSITE_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include "QFsm/Back/Aux/TransitionTypes.hpp"
#include "QFsm/Back/Aux/Contains.hpp"
#include "QFsm/Back/Aux/FsmType.hpp"
#include "QFsm/Back/Aux/Detail/Trace.hpp"
#include "QFsm/Back/Detail/OrthogonalRegions.hpp"
#include "QFsm/Back/Detail/Visitor.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{

template<typename TFsmBase, typename Enable = void> class Composite
{
public:
    template<typename Event> static bool execute(TFsmBase&, const Event&) { return false; }
};

template<typename TFsmBase>
class Composite<TFsmBase, typename boost::enable_if< Aux::Contains2<typename TFsmBase::Derived, Aux::InitState, Aux::TargetState, Aux::FsmType> >::type>
{
    typedef typename OrthogonalRegions<typename TFsmBase::Derived>::template ForEachRegion<> ForEachRegion;

    template<typename Event> class CompositeVisitor
    {
    public:
        CompositeVisitor(typename TFsmBase::Pool& p_pool, const Event& p_event, bool& p_isHandled)
            : m_pool(p_pool), m_event(p_event), m_isHandled(p_isHandled)
        { }

        template<typename Composite> void operator()(typename boost::enable_if< boost::is_base_of<Aux::FsmType, Composite> >::type* = 0) const
        {
            TRACE("process composite [%s]", typeid(Event).name());
            try {
            m_isHandled = (m_pool.template acquire<Composite>()).processEvent(m_event);
            } catch(...) { }
        }

        template<typename Composite> void operator()(typename boost::disable_if< boost::is_base_of<Aux::FsmType, Composite> >::type* = 0) const
        {
            TRACE_ERR("process composite [%s]", typeid(Event).name());
        }

    private:
        typename TFsmBase::Pool& m_pool;
        const Event& m_event;
        bool& m_isHandled;
    };

public:
    template<typename Event> static bool execute(TFsmBase& p_fsm, const Event& p_event)
    {
        bool l_isHandled = false;
        CompositeVisitor<Event> l_visitor(p_fsm.pool, p_event, l_isHandled);
        Visitor<TFsmBase>::template execute(p_fsm, l_visitor);
        return l_isHandled;
    }
};

} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

