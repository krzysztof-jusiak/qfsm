//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_OPERATIONS_DEFER_HPP
#define QFSM_FRONT_OPERATIONS_DEFER_HPP

#include <boost/bind.hpp>
#include "QFsm/Back/Aux/Internal.hpp"
#include "QFsm/Back/Aux/Operation.hpp"

namespace QFsm
{
namespace Front
{
namespace Operations
{

class Defer : Back::Aux::Internal
{
public:
    template<typename TEvent, typename TFsm> void operator()(const TEvent& p_event, TFsm& p_fsm) const
    {
        bool (TFsm::*l_ptr)(const TEvent&) = &TFsm::processEvent;
        p_fsm.deferralEvents.addDeferralEvent(boost::bind(l_ptr, &p_fsm, p_event));
    }
};

} // namespace Operations
} // namespace Front
} // namespace QFsm

#endif

