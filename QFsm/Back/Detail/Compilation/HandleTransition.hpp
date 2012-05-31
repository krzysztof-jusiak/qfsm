//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_COMPILATION_HANDLETRANSITION_HPP
#define QFSM_BACK_DETAIL_COMPILATION_HANDLETRANSITION_HPP

#include <boost/type_traits/is_base_of.hpp>
#include "QFsm/Front/Operations/Transition.hpp"
#include "QFsm/Back/Detail/Compilation/State.hpp"
#include "QFsm/Back/Aux/Extensions.hpp"
#include "QFsm/Back/Aux/Call.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{
namespace Compilation
{

template
<
    unsigned StateInitId,
    typename TStateInit,
    typename TEvent,
    typename TStateTarget,
    typename TAction,
    typename TGuard
>
class HandleTransition
{
public:
    template<typename Event, typename Fsm> static bool execute(const State& p_currentState, const Event& p_event, Fsm& p_fsm)
    {
        if (p_currentState.id == StateInitId && boost::is_base_of<Event, TEvent>::value)
        {
            Fsm::Log::template onEvent<TEvent, TStateInit>(p_fsm.pool);

            if (Aux::Call<bool, TGuard>::execute(p_event, p_fsm))
            {
                Aux::Call<void, TAction>::execute(p_event, p_fsm);
                return true;
            }
        }

        return false;
    }
};

} // namespace Compilation
} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

