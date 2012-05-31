//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include "QFsm/Front/Operations/And.hpp"
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

TEST(And, BasicBothTrue)
{
    //given
    typedef Guard<0, true> Guard1;
    typedef Guard<1, true> Guard2;
    Guard1::calls() = 0;
    Guard2::calls() = 0;
    FsmStubPool<Guard1, Guard2> l_fsm;

    //when
    EXPECT_TRUE((And<Guard1, Guard2>()(e1(), l_fsm)));

    //then
    EXPECT_EQ(1, Guard1::calls());
    EXPECT_EQ(1, Guard2::calls());
}

TEST(And, BasicSecondTrue)
{
    //given
    typedef Guard<0, false> Guard1;
    typedef Guard<1, true> Guard2;
    Guard1::calls() = 0;
    Guard2::calls() = 0;
    FsmStubPool<Guard1, Guard2> l_fsm;

    //when
    EXPECT_FALSE((And<Guard1, Guard2>()(e1(), l_fsm)));

    //then
    EXPECT_EQ(1, Guard1::calls());
    EXPECT_EQ(0, Guard2::calls());
}

TEST(And, BasicBothFalse)
{
    //given
    typedef Guard<0, false> Guard1;
    typedef Guard<1, false> Guard2;
    Guard1::calls() = 0;
    Guard2::calls() = 0;
    FsmStubPool<Guard1, Guard2> l_fsm;

    //when
    EXPECT_FALSE((And<Guard1, Guard2>()(e1(), l_fsm)));

    //then
    EXPECT_EQ(1, Guard1::calls());
    EXPECT_EQ(0, Guard2::calls());
}

TEST(And, OneTrue)
{
    //given
    typedef Guard<0, true> Guard1;
    Guard1::calls() = 0;
    FsmStubPool<Guard1> l_fsm;

    //when
    EXPECT_TRUE((And<Guard1>()(e1(), l_fsm)));

    //then
    EXPECT_EQ(1, Guard1::calls());
}

TEST(And, OneFalse)
{
    //given
    typedef Guard<0, false> Guard1;
    Guard1::calls() = 0;
    FsmStubPool<Guard1> l_fsm;

    //when
    EXPECT_FALSE((And<Guard1>()(e1(), l_fsm)));

    //then
    EXPECT_EQ(1, Guard1::calls());
}

TEST(And, ComplexFalse)
{
    //given
    typedef Guard<0, true> Guard1;
    typedef Guard<1, false> Guard2;
    typedef Guard<2, true> Guard3;

    Guard1::calls() = 0;
    Guard2::calls() = 0;
    Guard3::calls() = 0;
    FsmStubPool<Guard1, Guard2, Guard3> l_fsm;

    //when
    EXPECT_FALSE((And<Guard1, Guard2, Guard3>()(e1(), l_fsm)));

    //then
    EXPECT_EQ(1, Guard1::calls());
    EXPECT_EQ(1, Guard2::calls());
    EXPECT_EQ(0, Guard3::calls());
}

TEST(And, ComplexTrue)
{
    //given
    typedef Guard<0, true> Guard1;
    typedef Guard<1, true> Guard2;
    typedef Guard<2, true> Guard3;

    Guard1::calls() = 0;
    Guard2::calls() = 0;
    Guard3::calls() = 0;
    FsmStubPool<Guard1, Guard2, Guard3> l_fsm;

    //when
    EXPECT_TRUE((And<Guard1, Guard2, Guard3>()(e1(), l_fsm)));

    //then
    EXPECT_EQ(1, Guard1::calls());
    EXPECT_EQ(1, Guard2::calls());
    EXPECT_EQ(1, Guard3::calls());
}

} // namespace UT
} // namespace Operations
} // namespace Front
} // namespace QFsm

