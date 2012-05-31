//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include <boost/mpl/vector.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "QFsm/Back/Detail/DeferralEvent.hpp"
#include "QFsm/Front/Operations/Transition.hpp"
#include "QFsm/Front/Operations/None.hpp"
#include "QFsm/Front/Operations/Defer.hpp"
#include "Common/FsmStub.hpp"
#include "Common/Events.hpp"

namespace QFsm
{

using Front::Operations::Transition;
using Front::Operations::Defer;
using Front::Operations::_;
using namespace Test::Common;

namespace Back
{
namespace Detail
{
namespace UT
{

typedef boost::function<void()> ExecuteEvent;

TEST(DeferralEvent, NoDeferActions)
{
    //given
    typedef FsmStub< boost::mpl::vector< Transition<_, _, _> > > Fsm;
    DeferralEvent<Fsm> l_deferralEvent;

    //when
    l_deferralEvent.execute(true);

    //then
    verifyProcessEvent< boost::mpl::vector0<>, Fsm>();
}

TEST(DeferralEvent, BasicDefer)
{
    //given
    typedef FsmStub< boost::mpl::vector< Transition<_, e1, _, Defer> > > Fsm;
    Fsm l_fsm;
    DeferralEvent<Fsm> l_deferralEvent;
    bool (Fsm::*l_ptr)(const e1&) = &Fsm::processEvent;
    l_deferralEvent.addDeferralEvent(boost::bind(l_ptr, &l_fsm, e1()));
    l_deferralEvent.init();

    //when
    l_deferralEvent.execute(true);

    //then
    verifyProcessEvent< boost::mpl::vector1<e1>, Fsm>();
}

TEST(DeferralEvent, BasicDeferNoInit)
{
    //given
    typedef FsmStub< boost::mpl::vector< Transition<_, e1, _, Defer> > > Fsm;
    Fsm l_fsm;
    DeferralEvent<Fsm> l_deferralEvent;
    bool (Fsm::*l_ptr)(const e1&) = &Fsm::processEvent;
    l_deferralEvent.addDeferralEvent(boost::bind(l_ptr, &l_fsm, e1()));

    //when
    l_deferralEvent.execute(true);

    //then
    verifyProcessEvent< boost::mpl::vector<>, Fsm>();
}

TEST(DeferralEvent, BasicDeferNoaAdd)
{
    //given
    typedef FsmStub< boost::mpl::vector< Transition<_, e1, _, Defer> > > Fsm;
    DeferralEvent<Fsm> l_deferralEvent;
    l_deferralEvent.init();

    //when
    l_deferralEvent.execute(true);

    //then
    verifyProcessEvent< boost::mpl::vector<>, Fsm>();
}

TEST(DeferralEvent, BasicDeferHandledFalse)
{
    //given
    typedef FsmStub< boost::mpl::vector< Transition<_, e1, _, Defer> > > Fsm;
    Fsm l_fsm;
    DeferralEvent<Fsm> l_deferralEvent;
    bool (Fsm::*l_ptr)(const e1&) = &Fsm::processEvent;
    l_deferralEvent.addDeferralEvent(boost::bind(l_ptr, &l_fsm, e1()));
    l_deferralEvent.init();

    //when
    l_deferralEvent.execute(false);

    //then
    verifyProcessEvent< boost::mpl::vector0<>, Fsm>();
}

TEST(DeferralEvent, BasicDeferNoInitHandledFalse)
{
    //given
    typedef FsmStub< boost::mpl::vector< Transition<_, e1, _, Defer> > > Fsm;
    Fsm l_fsm;
    DeferralEvent<Fsm> l_deferralEvent;
    bool (Fsm::*l_ptr)(const e1&) = &Fsm::processEvent;
    l_deferralEvent.addDeferralEvent(boost::bind(l_ptr, &l_fsm, e1()));

    //when
    l_deferralEvent.execute(false);

    //then
    verifyProcessEvent< boost::mpl::vector<>, Fsm>();
}

TEST(DeferralEvent, BasicDeferNoaAddHandledFalse)
{
    //given
    typedef FsmStub< boost::mpl::vector< Transition<_, e1, _, Defer> > > Fsm;
    DeferralEvent<Fsm> l_deferralEvent;
    l_deferralEvent.init();

    //when
    l_deferralEvent.execute(false);

    //then
    verifyProcessEvent< boost::mpl::vector<>, Fsm>();
}

} // namespace UT
} // namespace Detail
} // namespace Back
} // namespace QFsm

