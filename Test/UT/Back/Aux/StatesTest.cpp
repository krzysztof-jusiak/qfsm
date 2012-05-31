//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include <boost/mpl/vector.hpp>
#include "QFsm/Back/Aux/States.hpp"
#include "QFsm/Front/Operations/Transition.hpp"
#include "QFsm/Front/Operations/None.hpp"
#include "Common/States.hpp"
#include "Common/Equal.hpp"

namespace QFsm
{

using Front::Operations::Transition;
using Front::Operations::_;
using namespace Test::Common;

namespace Back
{
namespace Aux
{
namespace UT
{

TEST(States, None)
{
    EXPECT_TRUE((
        Equal
        <
            boost::mpl::vector0<>,
            States< boost::mpl::vector0<> >::type
        >::value
    ));
}

TEST(States, Basic)
{
    EXPECT_TRUE((
        Equal
        <
            boost::mpl::vector
            <
                State1, State2
            >,
            States
            <
                boost::mpl::vector
                <
                    Transition<State1, _, State2>
                >
            >::type
        >::value
    ));
}

TEST(States, TheSame)
{
    EXPECT_TRUE((
        Equal
        <
            boost::mpl::vector
            <
                State1
            >,
            States
            <
                boost::mpl::vector
                <
                    Transition<State1, _, State1>
                >
            >::type
        >::value
    ));
}

TEST(States, Multi)
{
    EXPECT_TRUE((
        Equal
        <
            boost::mpl::vector
            <
                State1, State2, State3
            >,
            States
            <
                boost::mpl::vector
                <
                    Transition<State1, _, State2>,
                    Transition<State2, _, State3>
                >
            >::type
        >::value
    ));
}

} // namespace UT
} // namespace Aux
} // namespace Back
} // namespace QFsm

