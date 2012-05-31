//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_TEST_COMMON_VERIFYCURRENTSTATES_HPP
#define QFSM_TEST_COMMON_VERIFYCURRENTSTATES_HPP

#include <gtest/gtest.h>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>
#include "QFsm/Aux/PrintType.hpp"

namespace QFsm
{
namespace Test
{
namespace Common
{

template<typename ExpectedStates> class VerifyCurrentStates
{
public:
    VerifyCurrentStates()
        : current(0)
    { }

    template<typename State> void operator()() const
    {
        verify<ExpectedStates, State>(current);
        current++;
    }

private:
    template<typename Seq, typename State> void verify(unsigned = 0, typename boost::enable_if< boost::mpl::empty<Seq> >::type* = 0) const { }
    template<typename Seq, typename State> void verify(unsigned i = 0, typename boost::disable_if< boost::mpl::empty<Seq> >::type* = 0) const
    {
        typedef typename boost::mpl::front<Seq>::type type;

        if (i == current)
        {
            ASSERT_TRUE((boost::is_same<type, State>::value)) << "[" << current << "] " << QFsm::Aux::printType<type>() << " != " << QFsm::Aux::printType<State>();
        }

        verify<typename boost::mpl::pop_front<Seq>::type, State>(i + 1);
    }

    mutable unsigned current;
};

template<typename States, typename Fsm> void verifyCurrentStates(Fsm& p_fsm, typename boost::enable_if< boost::mpl::is_sequence<States> >::type* = 0)
{
    p_fsm.visitCurrentStates(VerifyCurrentStates<States>());
}

template<typename States, typename Fsm> void verifyCurrentStates(Fsm& p_fsm, typename boost::disable_if< boost::mpl::is_sequence<States> >::type* = 0)
{
    p_fsm.visitCurrentStates(VerifyCurrentStates< boost::mpl::vector<States> >());
}

} // namespace Common
} // namespace Test
} // namespace QFsm

#endif

