//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_OPERATIONS_NOT_HPP
#define QFSM_FRONT_OPERATIONS_NOT_HPP

#include "QFsm/Back/Aux/Operation.hpp"
#include "QFsm/Back/Aux/Call.hpp"

namespace QFsm
{
namespace Front
{
namespace Aux
{

template<typename TGuard, template<typename, typename> TCall = Back::Aux::Call>
class Not : public Back::Aux::Operation1<TGuard>
{
public:
    template<typename Event, typename Pool, typename CallBack>
    bool operator()(const Event& p_event, Pool& p_pool, const CallBack& p_callBack) const
    {
        return !TCall<bool, TGuard>::execute(p_event, p_pool, p_callBack);
    }
};

} // namespace Aux
} // namespace Front
} // namespace QFsm

#endif

