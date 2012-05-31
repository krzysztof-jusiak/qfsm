//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include <boost/mpl/vector.hpp>
#include "QFsm/Back/Aux/Events.hpp"
#include "QFsm/Front/Operations/Transition.hpp"
#include "Common/Events.hpp"
#include "Common/States.hpp"
#include "Common/Equal.hpp"

namespace QFsm
{

using namespace Test::Common;

namespace Back
{
namespace Aux
{
namespace UT
{

template<typename TTransitionTable> struct Fsm
{
    typedef TTransitionTable TransitionTable;
};

TEST(Events, None)
{
    EXPECT_TRUE((
        Equal
        <
            boost::mpl::vector0<>,
            Events< Fsm< boost::mpl::vector0<> > >::type
        >::value
    ));
}

TEST(Events, Basic)
{
    EXPECT_TRUE((
        Equal
        <
            boost::mpl::vector
            <
                e1, e2
            >,
            Events
            <
                Fsm
                <
                    boost::mpl::vector
                    <
                        Front::Operations::Transition<State1, e1, State2>,
                        Front::Operations::Transition<State2, e2, State3>
                    >
                >
            >::type
        >::value
    ));
}

TEST(Events, Unique)
{
    EXPECT_TRUE((
        Equal
        <
            boost::mpl::vector
            <
                e1, e2
            >,
            Events
            <
                Fsm
                <
                    boost::mpl::vector
                    <
                        Front::Operations::Transition<State1, e1, State2>,
                        Front::Operations::Transition<State2, e1, State3>,
                        Front::Operations::Transition<State2, e2, State3>,
                        Front::Operations::Transition<State2, e2, State3>
                    >
                >
            >::type
        >::value
    ));
}

TEST(Events, Complex)
{
    EXPECT_TRUE((
        Equal
        <
            boost::mpl::vector
            <
                e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16
            >,
            Events
            <
                Fsm
                <
                    boost::mpl::vector
                    <
                        Front::Operations::Transition<State1, e1, State2>,
                        Front::Operations::Transition<State2, e2, State3>,
                        Front::Operations::Transition<State2, e3, State3>,
                        Front::Operations::Transition<State2, e4, State3>,
                        Front::Operations::Transition<State2, e5, State3>,
                        Front::Operations::Transition<State2, e6, State3>,
                        Front::Operations::Transition<State2, e7, State3>,
                        Front::Operations::Transition<State2, e8, State3>,
                        Front::Operations::Transition<State2, e9, State3>,
                        Front::Operations::Transition<State2, e10, State3>,
                        Front::Operations::Transition<State2, e11, State3>,
                        Front::Operations::Transition<State2, e12, State3>,
                        Front::Operations::Transition<State2, e13, State3>,
                        Front::Operations::Transition<State2, e14, State3>,
                        Front::Operations::Transition<State2, e15, State3>,
                        Front::Operations::Transition<State2, e16, State3>
                    >
                >
            >::type
        >::value
    ));
}

} // namespace UT
} // namespace Aux
} // namespace Back
} // namespace QFsm

