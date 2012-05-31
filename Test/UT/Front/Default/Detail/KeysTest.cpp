//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include <boost/mpl/vector.hpp>
#include "QFsm/Back/Aux/FsmType.hpp"
#include "QFsm/Front/Default/Detail/Keys.hpp"
#include "QFsm/Front/Operations/Transition.hpp"
#include "QFsm/Front/Operations.hpp"
#include "Common/Guards.hpp"
#include "Common/Actions.hpp"
#include "Common/Equal.hpp"

namespace QFsm
{

using namespace Test::Common;
using namespace Front::Operations;

namespace Front
{
namespace Default
{
namespace Detail
{
namespace UT
{

class Ue { };
class Log { };
class Fsm1 : Back::Aux::FsmType { };
class Fsm2 : Back::Aux::FsmType { };
class Fsm3 : Back::Aux::FsmType { };
class Fsm4 : Back::Aux::FsmType { };

TEST(Keys, None)
{
    EXPECT_TRUE((
        Equal
        <
            boost::mpl::vector2<void, void>,
            Keys
            <
                boost::mpl::vector
                <
                    Transition<_, _, _>
                >,
                void,
                void
            >::type
        >::value
    ));
}

TEST(Keys, UnexpectedEventAndLogger)
{
    EXPECT_TRUE((
        Equal
        <
            boost::mpl::vector2<Ue, Log>,
            Keys
            <
                boost::mpl::vector
                <
                    Transition<_, _, _>
                >,
                Ue,
                Log
            >::type
        >::value
    ));
}

TEST(Keys, BasicGuardAndActions)
{
    EXPECT_TRUE((
        Equal
        <
            boost::mpl::vector<Ue, Log, Guard<0>, Guard<1>, Action<0>, Action<1> >,
            Keys
            <
                boost::mpl::vector
                <
                    Transition<_, _, _, _, Guard<0> >,
                    Transition<_, _, _, _, Guard<1> >,
                    Transition<_, _, _, Action<0> >,
                    Transition<_, _, _, Action<1> >
                >,
                Ue,
                Log
            >::type
        >::value
    ));
}

TEST(Keys, Opearations)
{
    EXPECT_TRUE((
        Equal
        <
            boost::mpl::vector<Ue, Log, Fsm1, Fsm2, Fsm3, Fsm4, Guard<0>, Guard<1>, Guard<3>, Action<1>, Action<2>, Action<3> >,
            Keys
            <
                boost::mpl::vector
                <
                    Transition<Fsm1, _, Fsm2, Seq< Action<1>, Action<2> >, And< Guard<0>, Guard<1>, Guard<3> > >,
                    Transition<Fsm3, _, _, _, Guard<0> >,
                    Transition<_, _, Fsm4, Action<3> >
                >,
                Ue,
                Log
            >::type
        >::value
    ));
}

} // namespace UT
} // namespace Detail
} // namespace Default
} // namespace Front
} // namespace QFsm

