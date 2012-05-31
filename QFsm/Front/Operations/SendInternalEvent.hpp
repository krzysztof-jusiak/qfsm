//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_OPERATIONS_SENDINTERNALEVENT_HPP
#define QFSM_FRONT_OPERATIONS_SENDINTERNALEVENT_HPP

#include <boost/type_traits/is_same.hpp>
#include "QFsm/Back/Aux/Operation.hpp"
#include "QFsm/Back/Aux/Call.hpp"

namespace QFsm
{
namespace Front
{
namespace Operations
{

class SendInternalEvent_ : Back::Aux::Internal { };

template<typename TInternalEvent, typename TAction>
class SendInternalEvent : public Back::Aux::Operation1<TAction>
{
public:
    typedef TAction Action;

    template<typename TEvent, typename TFsm> void operator()(const TEvent& p_event, TFsm& p_fsm) const
    {
        bool (TFsm::*l_ptr)(const TInternalEvent&) = &TFsm::processEvent;
        p_fsm.internalEvents.addInternalEvent(boost::bind(l_ptr, &p_fsm, Back::Aux::Call<TInternalEvent, TAction>::execute(p_event, p_fsm)));
    }
};

} // namespace Operations
} // namespace Front
} // namespace QFsm

#endif

