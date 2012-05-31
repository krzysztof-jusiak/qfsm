//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include "QFsm/Front/Operations/Seq.hpp"
#include "Common/Actions.hpp"
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

TEST(Seq, One)
{
    //given
    typedef Action<0> Action1;
    Action1::calls() = 0;
    FsmStubPool<Action1> l_fsm;

    //when
    Seq<Action1>()(e1(), l_fsm);

    //then
    EXPECT_EQ(1, Action1::calls());
}

TEST(Seq, Basic)
{
    //given
    typedef Action<0> Action1;
    typedef Action<1> Action2;
    Action1::calls() = 0;
    Action2::calls() = 0;
    FsmStubPool<Action1, Action2> l_fsm;

    //when
    Seq<Action1, Action2>()(e1(), l_fsm);

    //then
    EXPECT_EQ(1, Action1::calls());
    EXPECT_EQ(1, Action2::calls());
}

TEST(Seq, Complex)
{
    //given
    typedef Action<0> Action1;
    typedef Action<1> Action2;
    typedef Action<2> Action3;
    Action1::calls() = 0;
    Action2::calls() = 0;
    Action3::calls() = 0;
    FsmStubPool<Action1, Action2, Action3> l_fsm;

    //when
    Seq<Action1, Action2, Action3>()(e1(), l_fsm);

    //then
    EXPECT_EQ(1, Action1::calls());
    EXPECT_EQ(1, Action2::calls());
    EXPECT_EQ(1, Action3::calls());
}

} // namespace UT
} // namespace Operations
} // namespace Front
} // namespace QFsm

