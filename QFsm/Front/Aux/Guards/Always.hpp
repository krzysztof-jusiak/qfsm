//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_OPERATIONS_DEFER_HPP
#define QFSM_FRONT_OPERATIONS_DEFER_HPP

#include "QFsm/Back/Aux/Extensions.hpp"
#include "QFsm/Back/Aux/Internal.hpp"
#include "QFsm/Back/Aux/Operation.hpp"

namespace QFsm
{
namespace Front
{
namespace Operations
{

class Else
{
public:
    template<typename Event>
    bool operator()(const Event&) const
    {
        return true;
    }
};

} // namespace Operations
} // namespace Front
} // namespace QFsm

#endif

