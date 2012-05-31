//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_AUX_SILENTUNEXPECTEDHANDLER_HPP
#define QFSM_FRONT_AUX_SILENTUNEXPECTEDHANDLER_HPP

#include <exception>
#include "QFsm/Back/Aux/Trace.hpp"
#include "QFsm/Front/CUnexpectedHandler.hpp"

namespace QFsm
{
namespace Front
{
namespace Aux
{

class SilentUnexpectedHandler : public QFsm::Front::CUnexpectedHandler<SilentUnexpectedHandler>
{
public:
    template<typename Event, typename State> void operator()(const Event&)
    {
        QFSM_TRACE("Unexpected event [%s] received in state [%s]", typeid(Event).name(), typeid(State).name());
    }

    template<typename T> void operator()(const std::exception& QFSM_UNUSED(p_exception))
    {
        QFSM_TRACE("Exception caught [%s] in guard/action [%s]", p_exception.what(), typeid(T).name());
    }
};

} // namespace Aux
} // namespace Front
} // namespace QFsm

#endif

