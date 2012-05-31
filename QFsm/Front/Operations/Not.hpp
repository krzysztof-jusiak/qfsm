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
namespace Operations
{

template<typename TGuard>
class Not : public Back::Aux::Operation1<TGuard>
{
public:
    template<typename TFsm, typename TEvent> bool operator()(const TEvent& p_event, const TFsm& p_fsm) const
    {
        return !Back::Aux::Call<bool, TGuard>::execute(p_event, p_fsm);
    }
};

} // namespace Operations
} // namespace Front
} // namespace QFsm

#endif

