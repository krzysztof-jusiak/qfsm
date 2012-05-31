//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include <boost/mpl/vector.hpp>
#include "QFsm/Back/Detail/HandleEvent.hpp"
#include "QFsm/Front/Operations/Transition.hpp"
#include "QFsm/Front/Operations/None.hpp"
#include "Common/FsmStub.hpp"
#include "Common/Events.hpp"

namespace QFsm
{

using Front::Operations::_;
using namespace Test::Common;

namespace Back
{
namespace Detail
{
namespace UT
{

TEST(HandleEvent, Basic)
{
    //given
/*    typedef FsmStub< boost::mpl::vector< Front::Operations::Transition_<_, _, _> > > Fsm;*/
    /*Fsm l_fsm;*/

    //when
    //HandleEvent<Fsm>::execute(l_fsm, l_handle);

    //then
    //verifyProcessEventImpl< boost::mpl::vector<>, Fsm>();
}

} // namespace UT
} // namespace Detail
} // namespace Back
} // namespace QFsm

