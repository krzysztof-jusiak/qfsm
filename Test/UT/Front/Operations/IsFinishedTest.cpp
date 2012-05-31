//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include <boost/mpl/vector.hpp>
#include <boost/typeof/typeof.hpp>
#include "QFsm/Front/Operations/IsFinished.hpp"
#include "QFsm/Front/Operations/Transition.hpp"
#include "QFsm/Front/Operations/None.hpp"
#include "Common/Events.hpp"
#include "Common/States.hpp"
#include "Common/FsmStub.hpp"

namespace QFsm
{

using namespace Test::Common;

namespace Front
{
namespace Operations
{
namespace UT
{

TEST(IsFinished, Basic)
{
    //given
    typedef FsmStub
    <
        boost::mpl::vector
        <
            Transition<State1, e1, State2>
        >,
        State1
    >
    Fsm;
    Fsm l_fsm;
    l_fsm.currentStates[0] = 0;

    //when
    IsFinished<State1>()(e1(), l_fsm);

    //then
    //EXPECT_EQ(1u, l_fsm.deferralEvents.addDeferralEventCalls.size());
}

} // namespace UT
} // namespace Operations
} // namespace Front
} // namespace QFsm

