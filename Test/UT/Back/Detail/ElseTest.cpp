//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include <boost/mpl/vector.hpp>
#include "QFsm/Back/Detail/Else.hpp"
#include "QFsm/Front/Operations/Transition.hpp"
#include "QFsm/Front/Operations/None.hpp"
#include "QFsm/Front/Operations/Else.hpp"
#include "Common/FsmStub.hpp"
#include "Common/Events.hpp"

namespace QFsm
{

using Front::Operations::Transition;
using Front::Operations::_;
using namespace Test::Common;
typedef Front::Operations::Else Else_;

namespace Back
{
namespace Detail
{
namespace UT
{

TEST(Else, NoElseEventsHandleTrue)
{
    //given
    typedef FsmStub< boost::mpl::vector< Transition<_, _, _> > > Fsm;
    Fsm l_fsm;
    bool l_handle = true;

    //when
    Else<Fsm>::execute(l_fsm, l_handle);

    //then
    EXPECT_TRUE(l_handle);
    verifyProcessEventImpl< boost::mpl::vector<>, Fsm>();
}

TEST(Else, NoElseEventsHandleFalse)
{
    //given
    typedef FsmStub< boost::mpl::vector< Transition<_, _, _> > > Fsm;
    Fsm l_fsm;
    bool l_handle = false;

    //when
    Else<Fsm>::execute(l_fsm, l_handle);

    //then
    EXPECT_FALSE(l_handle);
    verifyProcessEventImpl< boost::mpl::vector<>, Fsm>();
}

TEST(Else, BasicHandleTrue)
{
    //given
    typedef FsmStub< boost::mpl::vector< Transition<_, Else_, _> > > Fsm;
    Fsm l_fsm;
    bool l_handle = true;

    //when
    Else<Fsm>::execute(l_fsm, l_handle);

    //then
    EXPECT_TRUE(l_handle);
    verifyProcessEventImpl< boost::mpl::vector0<>, Fsm>();
}

TEST(Else, BasicHandleFalse)
{
    //given
    typedef FsmStub< boost::mpl::vector< Transition<_, Else_, _> > > Fsm;
    Fsm l_fsm;
    bool l_handle = false;

    //when
    Else<Fsm>::execute(l_fsm, l_handle);

    //then
    EXPECT_TRUE(l_handle);
    verifyProcessEventImpl< boost::mpl::vector1<Else_>, Fsm>();
}

} // namespace UT
} // namespace Detail
} // namespace Back
} // namespace QFsm

