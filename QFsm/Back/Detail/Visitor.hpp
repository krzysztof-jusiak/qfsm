//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_VISITOR_HPP
#define QFSM_BACK_DETAIL_VISITOR_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include "QFsm/Back/Aux/Detail/Trace.hpp"
#include "QFsm/Back/Aux/TransitionTypes.hpp"
#include "QFsm/Back/Aux/Contains.hpp"
#include "QFsm/Back/Aux/State.hpp"
#include "QFsm/Back/Detail/OrthogonalRegions.hpp"
#include "QFsm/Front/Operations/None.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{

template<typename TFsmBase>
class Visitor
{
    typedef typename OrthogonalRegions<typename TFsmBase::Derived>::template ForEachRegion<> ForEachRegion;

    class VisitorImpl
    {
        template<typename Seq, typename Visitor> inline static void forEach(const typename TFsmBase::State&, Visitor&, typename boost::enable_if< boost::mpl::empty<Seq> >::type* = 0) { }
        template<typename Seq, typename Visitor> inline static void forEach(const typename TFsmBase::State& p_state, Visitor& p_visitor, typename boost::disable_if< boost::mpl::empty<Seq> >::type* = 0)
        {
            if (Aux::State<typename TFsmBase::State, typename TFsmBase::Fsm>::template equals<typename boost::mpl::front<Seq>::type>(p_state))
            {
                p_visitor.template operator()<typename boost::mpl::front<Seq>::type>();
                return;
            }

            forEach<typename boost::mpl::pop_front<Seq>::type>(p_state, p_visitor);
        }

    public:
        template<typename Region, typename Visitor> static void execute(TFsmBase& p_fsm, Visitor& p_visitor)
        {
            TRACE("visit [%s][%d]", typeid(Visitor).name(), int(Region::value));
            forEach<typename TFsmBase::States>(p_fsm.currentStates[Region::value], p_visitor);
        }
    };

public:
    template<typename Visitor> static void execute(TFsmBase& p_fsm, Visitor& p_visitor)
    {
        ForEachRegion::template execute<VisitorImpl>(p_fsm, p_visitor);
    }
};

} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

