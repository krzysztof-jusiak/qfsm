//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_OPERATIONS_BIND_HPP
#define QFSM_FRONT_OPERATIONS_BIND_HPP

#include "QFsm/Back/Aux/Internal.hpp"

namespace QFsm
{
namespace Front
{
namespace Operations
{

template<typename Event, typename Class, void (Class::*ptr)(const Event&)>
class Bind : Back::Aux::Internal
{
public:
    template<typename TEvent, typename TFsm> void operator()(const TEvent& p_event, TFsm&) const
    {
        ptr(p_event);
    }
};

} // namespace Operations
} // namespace Front
} // namespace QFsm

#endif

