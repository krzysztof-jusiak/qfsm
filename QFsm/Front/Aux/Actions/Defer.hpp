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

QFSM_UML_EXTENSIONS
(
    class Defer : Back::Aux::Internal
    {
    public:
        template<typename Event, typename Pool, typename CallBack>
        void operator()(const Event& p_event, Pool&, const CallBack& p_callBack) const
        {
            p_callBack.deferEvent(p_event);
        }
    };
)

} // namespace Operations
} // namespace Front
} // namespace QFsm

#endif

