//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_OPERATIONS_INTERRUPT_HPP
#define QFSM_FRONT_OPERATIONS_INTERRUPT_HPP

#include "QFsm/Back/Aux/Extensions.hpp"
#include "QFsm/Back/Aux/Internal.hpp"

namespace QFsm
{
namespace Front
{
namespace Operations
{

QFSM_NON_UML_EXTENSIONS
(
    class Interrupt_ : Back::Aux::Internal { };

    template<typename Event> class Interrupt : Interrupt_
    {
    public:
        typedef Event type;
    };
)

} // namespace Operations
} // namespace Front
} // namespace QFsm

#endif

