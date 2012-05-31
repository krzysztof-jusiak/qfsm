//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include <boost/mpl/vector.hpp>
#include "QFsm/Back/Detail/CompletionTransition.hpp"
#include "QFsm/Front/Operations/Transition.hpp"
#include "QFsm/Front/Operations/None.hpp"
#include "Common/FsmStub.hpp"

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

TEST(CompletionTransition, NoCompletionTransitions)
{
    //given
    typedef FsmStub< boost::mpl::vector< Transition<_, int, _> > > Fsm;
    Fsm l_fsm;

    //when
    CompletionTransition<Fsm>::execute(l_fsm);

    //then
    verifyProcessEventImpl< boost::mpl::vector0<>, Fsm>();
}

TEST(CompletionTransition, CompletionTransitionsHandleTrue)
{
    //given
    typedef FsmStub< boost::mpl::vector< Transition<_, _, _> > > Fsm;
    Fsm l_fsm;

    //when
    CompletionTransition<Fsm>::execute(l_fsm, true);

    //then
    verifyProcessEventImpl< boost::mpl::vector1<_>, Fsm>();
}

TEST(CompletionTransition, CompletionTransitionsHandleFalse)
{
    //given
    typedef FsmStub< boost::mpl::vector< Transition<_, _, _> > > Fsm;
    Fsm l_fsm;

    //when
    CompletionTransition<Fsm>::execute(l_fsm, false);

    //then
    verifyProcessEventImpl< boost::mpl::vector0<>, Fsm>();
}

} // namespace UT
} // namespace Detail
} // namespace Back
} // namespace QFsm

