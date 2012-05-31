//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_ELSE_HPP
#define QFSM_BACK_DETAIL_ELSE_HPP

#include <boost/utility/enable_if.hpp>
#include "QFsm/Back/Aux/TransitionTypes.hpp"
#include "QFsm/Back/Aux/Contains.hpp"
#include "QFsm/Front/Operations/Else.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{

template<typename TFsmBase, typename Enable = void> class Else
{
public:
    static void execute(TFsmBase&, bool&) { }
};

template<typename TFsmBase>
class Else<TFsmBase, typename boost::enable_if< Aux::Contains<typename TFsmBase::Derived, Aux::Event, Front::Operations::Else> >::type>
{
public:
    static void execute(TFsmBase& p_fsm, bool& p_handled)
    {
        if (!p_handled)
        {
            p_handled = p_fsm.processEventImpl(Front::Operations::Else());
        }
    }
};

} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

