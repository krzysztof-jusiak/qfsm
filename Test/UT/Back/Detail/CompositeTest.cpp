//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include <boost/mpl/vector.hpp>
#include "QFsm/Back/Detail/Composite.hpp"
#include "QFsm/Front/Operations/Transition.hpp"
#include "QFsm/Front/Operations/None.hpp"
#include "Common/FsmStub.hpp"
#include "Common/Events.hpp"

namespace QFsm
{

using Front::Operations::Transition;
using Front::Operations::_;
using namespace Test::Common;

namespace Back
{
namespace Detail
{
namespace UT
{

TEST(Composite, NoCompletionTransitions)
{
    //given
    typedef FsmStub< boost::mpl::vector< Transition<_, e1, _> > > Fsm;
    Fsm l_fsm;

    //when & then
    EXPECT_FALSE(Composite<Fsm>::execute(l_fsm, e1()));
}

TEST(Composite, InitStateFsmHandleTrue)
{
    //given
    typedef FsmStub< boost::mpl::vector< Transition<_, e1, _> > > CompositeFsm;
    typedef FsmStub< boost::mpl::vector< Transition<CompositeFsm, e1, _> > > Fsm;
    Fsm l_fsm;

    //when
    EXPECT_TRUE(Composite<Fsm>::execute(l_fsm, e1()));

    //then
    verifyProcessEvent< boost::mpl::vector1<e1>, CompositeFsm>();
}

TEST(Composite, InitStateFsmHandleFalse)
{
    //given
    typedef FsmStub< boost::mpl::vector< Transition<_, e2, _> > > CompositeFsm;
    typedef FsmStub< boost::mpl::vector< Transition<CompositeFsm, e1, _> > > Fsm;
    Fsm l_fsm;

    //when
    EXPECT_FALSE(Composite<Fsm>::execute(l_fsm, e1()));

    //then
    verifyProcessEvent< boost::mpl::vector<>, CompositeFsm>();
}

} // namespace UT
} // namespace Detail
} // namespace Back
} // namespace QFsm

