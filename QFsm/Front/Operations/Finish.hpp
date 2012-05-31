//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_OPERATIONS_FINISH_HPP
#define QFSM_FRONT_OPERATIONS_FINISH_HPP

#include "QFsm/Back/Aux/Internal.hpp"

namespace QFsm
{
namespace Front
{
namespace Operations
{

/**
 * Helpful class to identify automatic exit from orthogonal region
 */
class Finish : Back::Aux::Internal { };

} // namespace Operations
} // namespace Front
} // namespace QFsm

#endif

