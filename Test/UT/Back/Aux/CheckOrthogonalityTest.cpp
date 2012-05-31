//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/equal.hpp>
#include "QFsm/Front/Operations/Transition.hpp"
#include "QFsm/Back/Aux/CheckOrthogonality.hpp"
#include "Common/States.hpp"
#include "Common/Events.hpp"

namespace QFsm
{

using Front::Operations::Transition;
using namespace Test::Common;

namespace Back
{
namespace Aux
{
namespace UT
{

class Orthogonality { };

TEST(CheckOrthogonality, OneState)
{
    EXPECT_TRUE((
        CheckOrthogonality
        <
            Orthogonality,
            State1,
            boost::mpl::vector
            <
                Transition<State1, e1, State2>
            >
        >::type::value
    ));
}

TEST(CheckOrthogonality, ManyStates)
{
    EXPECT_TRUE((
        CheckOrthogonality
        <
            Orthogonality,
            State1,
            boost::mpl::vector
            <
                Transition<State1, e1, State2>,
                Transition<State2, e2, State3>,
                Transition<State3, e3, State4>
            >
        >::type::value
    ));
}

TEST(CheckOrthogonality, TwoInitialStates)
{
    EXPECT_TRUE((
        CheckOrthogonality
        <
            Orthogonality,
            boost::mpl::vector<State1, State3>,
            boost::mpl::vector
            <
                Transition<State1, e1, State2>,
                Transition<State3, e2, State4>
            >
        >::type::value
    ));
}

TEST(CheckOrthogonality, TwoInitialStatesFail)
{
    EXPECT_FALSE((
        CheckOrthogonality
        <
            Orthogonality,
            boost::mpl::vector<State1, State3>,
            boost::mpl::vector
            <
                Transition<State1, e1, State2>,
                Transition<State2, e1, State3>,
                Transition<State3, e2, State4>
            >,
            false /*no assert*/
        >::type::value
    ));
}

TEST(CheckOrthogonality, TwoInitialStatesCircularFail)
{
    EXPECT_FALSE((
        CheckOrthogonality
        <
            Orthogonality,
            boost::mpl::vector<State1, State3>,
            boost::mpl::vector
            <
                Transition<State1, e1, State1>,
                Transition<State2, e1, State3>,
                Transition<State3, e2, State2>,
                Transition<State2, e2, State1>
            >,
            false /*no assert*/
        >::type::value
    ));
}

TEST(CheckOrthogonality, MoreInitialStatesEmpty)
{
    EXPECT_TRUE((
        CheckOrthogonality
        <
            Orthogonality,
            boost::mpl::vector<State1, State3, State5>,
            boost::mpl::vector
            <
                Transition<State1, e1, State2>,
                Transition<State3, e3, State4>,
                Transition<State5, e2, State5>
            >,
            false /*no assert*/
        >::type::value
    ));
}

TEST(CheckOrthogonality, MoreInitialStatesManyTransitionsFromOneState)
{
    EXPECT_TRUE((
        CheckOrthogonality
        <
            Orthogonality,
            boost::mpl::vector<State1, State3, State5>,
            boost::mpl::vector
            <
                Transition<State1, e1, State2>,
                Transition<State3, e3, State4>,
                Transition<State5, e2, State5>,
                Transition<State5, e3, State6>,
                Transition<State5, e1, State7>
            >,
            false /*no assert*/
        >::type::value
    ));
}

TEST(CheckOrthogonality, MoreInitialStatesManyTransitionsFail)
{
    EXPECT_FALSE((
        CheckOrthogonality
        <
            Orthogonality,
            boost::mpl::vector<State1, State3, State5>,
            boost::mpl::vector
            <
                Transition<State1, e1, State2>,
                Transition<State3, e3, State4>,
                Transition<State5, e2, State5>,
                Transition<State5, e3, State6>,
                Transition<State6, e1, State4>
            >,
            false /*no assert*/
        >::type::value
    ));
}

TEST(CheckOrthogonality, VerifyConflictedStatesEmpty)
{
    EXPECT_TRUE((
        boost::mpl::equal
        <
            boost::mpl::vector<>,
            CheckOrthogonality
            <
                Orthogonality,
                boost::mpl::vector<State1, State3, State5>,
                boost::mpl::vector
                <
                    Transition<State1, e1, State2>,
                    Transition<State3, e3, State4>,
                    Transition<State5, e2, State5>
                >,
                false /*no assert*/
            >::type
        >::value
    ));
}

TEST(CheckOrthogonality, VerifyConflictedStatesOneConlict)
{
    EXPECT_FALSE((
        boost::mpl::equal
        <
            boost::mpl::vector<State1>,
            CheckOrthogonality
            <
                Orthogonality,
                boost::mpl::vector<State1, State3, State5>,
                boost::mpl::vector
                <
                    Transition<State1, e1, State2>,
                    Transition<State3, e1, State1>
                >,
                false /*no assert*/
            >::type
        >::value
    ));
}

TEST(CheckOrthogonality, VerifyConflictedStatesManyConlicts)
{
    EXPECT_FALSE((
        boost::mpl::equal
        <
            boost::mpl::vector<State1, State4>,
            CheckOrthogonality
            <
                Orthogonality,
                boost::mpl::vector<State1, State3, State5>,
                boost::mpl::vector
                <
                    Transition<State1, e1, State2>,
                    Transition<State2, e1, State4>,
                    Transition<State3, e2, State1>,
                    Transition<State5, e3, State6>,
                    Transition<State6, e2, State4>
                >,
                false /*no assert*/
            >::type
        >::value
    ));
}

TEST(CheckOrthogonality, void)
{
    EXPECT_TRUE((
        CheckOrthogonality
        <
            void,
            boost::mpl::vector0<>,
            boost::mpl::vector0<>
        >::type::value
    ));
}

} // namespace UT
} // namespace Aux
} // namespace Back
} // namespace QFsm

