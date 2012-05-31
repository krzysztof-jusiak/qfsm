//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "gtest/gtest.h"
#include "Common/FsmTest.hpp"
#include "Common/Events.hpp"
#include "Common/States.hpp"
#include "Common/Actions.hpp"
#include "Common/Guards.hpp"
#include "Common/VerifyCurrentStates.hpp"

namespace QFsm
{

using namespace Test::Common;
using namespace Front::Operations;

namespace Utility
{
namespace MT
{

FSM_TEST(FsmTestBasicFeatures,
    State1,
    boost::mpl::vector
    <
        Transition < State1 , e1 , State2 , None   >,
        Transition < State2 , e2 , State3 , Action<0> >
    >,
    Back::UnexpectedEvent,
    Back::LoggerDisabled
);

TYPED_TEST(FsmTestBasicFeatures, FsmCtor)
{
    //when & then
    verifyCurrentStates<State1>(*this->template m_fsm);
}

TYPED_TEST(FsmTestBasicFeatures, FsmStart)
{
    //when
    this->template m_fsm->start();

    //then
    verifyCurrentStates<State1>(*this->template m_fsm);
}

TYPED_TEST(FsmTestBasicFeatures, BasicProcessEvent)
{
    //given
    this->template m_fsm->start();

    //when
    EXPECT_TRUE(this->template m_fsm->processEvent(e1()));

    //then
    verifyCurrentStates<State2>(*this->template m_fsm);
}

TYPED_TEST(FsmTestBasicFeatures, UnexpectedProcessEvent)
{
    //given
    this->template m_fsm->start();

    //when
    EXPECT_FALSE(this->template m_fsm->processEvent(unexpected_event()));

    //then
    verifyCurrentStates<State1>(*this->template m_fsm);
}

TYPED_TEST(FsmTestBasicFeatures, Action)
{
    //given
    typedef Action<0> Action;
    Action::calls() = 0;
    this->template m_fsm->processEvent(e1());

    //when
    EXPECT_TRUE(this->template m_fsm->processEvent(e2()));

    //then
    EXPECT_EQ(1, Action::calls());
    verifyCurrentStates<State3>(*this->template m_fsm);
}

} // namespace MT
} // namespace Utility
} // namespace QFsm

