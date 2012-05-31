//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_TERMINATE_HPP
#define QFSM_BACK_DETAIL_TERMINATE_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include "QFsm/Back/Aux/TransitionTypes.hpp"
#include "QFsm/Back/Aux/Contains.hpp"
#include "QFsm/Back/Detail/Visitor.hpp"
#include "QFsm/Back/Detail/UnexpectedEvent.hpp"
#include "QFsm/Front/Operations/Terminate.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{

template<typename TFsmBase, typename Enable = void> class Terminate
{
public:
    template<typename Event> static bool execute(TFsmBase&, const Event&) { return true; }
};

template<typename TFsmBase>
class Terminate<TFsmBase, typename boost::enable_if< Aux::Contains<typename TFsmBase::Derived, Aux::TargetState, Front::Operations::Terminate> >::type>
{
    class IsTerminatedVisitor
    {
    public:
        explicit IsTerminatedVisitor(bool& p_isTerminated)
            : m_isTerminated(p_isTerminated)
        { }

        template<typename State> void operator()() const
        {
            m_isTerminated = m_isTerminated || boost::is_base_of<Front::Operations::Terminate, State>::value;
        }

    private:
        bool& m_isTerminated;
    };

public:
    template<typename Event> static bool execute(TFsmBase& p_fsm, const Event& p_event)
    {
        bool l_isTerminated = false;

        //search if any state of all regions is in terminated state
        IsTerminatedVisitor l_visitor(l_isTerminated);
        Detail::Visitor<TFsmBase>(p_fsm, l_visitor);

        if (l_isTerminated)
        {
            return UnexpectedEvent<TFsmBase>::execute(p_fsm, p_event, !l_isTerminated);
        }

        return true;
    }
};

} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

