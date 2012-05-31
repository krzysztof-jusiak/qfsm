//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_FSMINTERNAL_HPP
#define QFSM_BACK_FSMINTERNAL_HPP

#include "QFsm/Back/Aux/Extensions.hpp"
#include "QFsm/Back/Aux/Detail/Ctor.hpp"

namespace QFsm
{
namespace Back
{

template<typename TFsm>
class FsmInternal : public TFsm
{
private:
    using TFsm::pool;
    using TFsm::currentStates;
    using TFsm::processEventImpl;
    QFSM_UML_EXTENSIONS(using TFsm::deferralEvents;)
    QFSM_UML_EXTENSIONS(using TFsm::internalEvents;)

public:
    CTOR_REF(FsmInternal, TFsm, { })
};

} // namespace Back
} // namespace QFsm

#endif

