//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include <boost/typeof/typeof.hpp>
#include "QFsm/Front/Operations/Bind.hpp"
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

class BindAction
{
public:
    static void handleStatic(const e1&)
    {
        calls()++;
    }

    void handle(const e1&)
    {
        calls()++;
    }

    static int& calls()
    {
        static int s_calls = 0;
        return s_calls;
    }
};

template<bool Result>
class BindGuard
{
public:
    static bool handleStatic(const e1&)
    {
        calls()++;
        return Result;
    }

    bool handle(const e1&)
    {
        calls()++;
        return Result;
    }

    static int& calls()
    {
        static int s_calls = 0;
        return s_calls;
    }
};

TEST(Bind, BasicActionStatic)
{
    //given
    FsmStubPool<> l_fsm;
    BindAction::calls() = 0;

    //when
    Bind<BOOST_TYPEOF(&BindAction::handleStatic), &BindAction::handleStatic>()(e1(), l_fsm);

    //then
    EXPECT_EQ(1, BindAction::calls());
}

TEST(Bind, BasicActionDynamic)
{
    //given
    FsmStubPool<BindAction> l_fsm;
    BindAction::calls() = 0;

    //when
    Bind<BOOST_TYPEOF(&BindAction::handle), &BindAction::handle>()(e1(), l_fsm);

    //then
    EXPECT_EQ(1, BindAction::calls());
}

TEST(Bind, BasicGuardStaticTrue)
{
    //given
    typedef BindGuard<true> BindGuard;
    FsmStubPool<> l_fsm;
    BindGuard::calls() = 0;

    //when
    EXPECT_TRUE((Bind<BOOST_TYPEOF(&BindGuard::handleStatic), &BindGuard::handleStatic>()(e1(), l_fsm)));

    //then
    EXPECT_EQ(1, BindGuard::calls());
}

TEST(Bind, BasicGuardStaticFalse)
{
    //given
    typedef BindGuard<false> BindGuard;
    FsmStubPool<> l_fsm;
    BindGuard::calls() = 0;

    //when
    EXPECT_FALSE((Bind<BOOST_TYPEOF(&BindGuard::handleStatic), &BindGuard::handleStatic>()(e1(), l_fsm)));

    //then
    EXPECT_EQ(1, BindGuard::calls());
}

TEST(Bind, BasicGuardDynamicFalse)
{
    //given
    typedef BindGuard<false> BindGuard;
    FsmStubPool<BindGuard> l_fsm;
    BindGuard::calls() = 0;

    //when
    EXPECT_FALSE((Bind<BOOST_TYPEOF(&BindGuard::handle), &BindGuard::handle>()(e1(), l_fsm)));

    //then
    EXPECT_EQ(1, BindGuard::calls());
}

TEST(Bind, BasicGuardDynamicTrue)
{
    //given
    typedef BindGuard<true> BindGuard;
    FsmStubPool<BindGuard> l_fsm;
    BindGuard::calls() = 0;

    //when
    EXPECT_TRUE((Bind<BOOST_TYPEOF(&BindGuard::handle), &BindGuard::handle>()(e1(), l_fsm)));

    //then
    EXPECT_EQ(1, BindGuard::calls());
}

TEST(Bind, QFSM_BIND)
{
    //given
    FsmStubPool<> l_fsm;
    BindAction::calls() = 0;

    //when
    QFSM_BIND(&BindAction::handleStatic)()(e1(), l_fsm);

    //then
    EXPECT_EQ(1, BindAction::calls());
}

} // namespace UT
} // namespace Operations
} // namespace Front
} // namespace QFsm

