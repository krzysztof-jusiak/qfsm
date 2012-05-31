//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include "QFsm/Front/Operations/Not.hpp"
#include "Common/Guards.hpp"
#include "Common/Events.hpp"
#include "Common/FsmStubPool.hpp"

namespace QFsm
{

using namespace Test::Common;

namespace Front
{
namespace Operations
{
namespace UT
{

TEST(Not, True)
{
    //given
    typedef Guard<0, true> Guard1;
    Guard1::calls() = 0;
    FsmStubPool<Guard1> l_fsm;

    //when
    EXPECT_FALSE((Not<Guard1>()(e1(), l_fsm)));

    //then
    EXPECT_EQ(1, Guard1::calls());
}

TEST(Not, False)
{
    //given
    typedef Guard<0, false> Guard1;
    Guard1::calls() = 0;
    FsmStubPool<Guard1> l_fsm;

    //when
    EXPECT_TRUE((Not<Guard1>()(e1(), l_fsm)));

    //then
    EXPECT_EQ(1, Guard1::calls());
}

} // namespace UT
} // namespace Operations
} // namespace Front
} // namespace QFsm

