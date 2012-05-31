//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include <boost/mpl/vector.hpp>
#include "QFsm/Back/Aux/TransitionTypes.hpp"
#include "QFsm/Front/Operations/Transition.hpp"
#include "QFsm/Front/Operations/None.hpp"
#include "QFsm/Back/Aux/Contains.hpp"

namespace QFsm
{

using Front::Operations::Transition;
using Front::Operations::_;

namespace Back
{
namespace Aux
{
namespace UT
{

template<typename TSeq>
struct Derived
{
    typedef TSeq TransitionTable;
};

class e_ { };
class e : public e_
{ };

class a_ { };
class a : public a_
{ };

class g_ { };
class g : public g_
{ };

TEST(Contains, Empty)
{
    EXPECT_FALSE((Contains<Derived<boost::mpl::vector0<> >, Event, e_>::value));
}

TEST(Contains, Operations)
{
    EXPECT_TRUE((Contains<Derived<boost::mpl::vector<Transition<_, e, _> > >, Event, e_>::value));
    EXPECT_TRUE((Contains<Derived<boost::mpl::vector<Transition<_, _, _, a, _> > >, Action, a_>::value));
    EXPECT_TRUE((Contains<Derived<boost::mpl::vector<Transition<_, _, _, _, g> > >, Guard, g_>::value));
}

TEST(Contains, OperationsNegative)
{
    EXPECT_FALSE((Contains<Derived<boost::mpl::vector<Transition<_, e, _> > >, Guard, e_>::value));
    EXPECT_FALSE((Contains<Derived<boost::mpl::vector<Transition<_, _, _, a, _> > >, Event, a_>::value));
    EXPECT_FALSE((Contains<Derived<boost::mpl::vector<Transition<_, _, _, _, g> > >, Action, g_>::value));
}

TEST(Contains2, Empty)
{
    EXPECT_FALSE((Contains2<Derived<boost::mpl::vector0<> >, Event, Guard, e_>::value));
}

TEST(Contains2, Operations)
{
    EXPECT_TRUE((Contains2<Derived<boost::mpl::vector<Transition<_, e, _> > >, Event, Guard, e_>::value));
    EXPECT_TRUE((Contains2<Derived<boost::mpl::vector<Transition<_, _, _, _, e> > >, Event, Guard, e_>::value));
}

TEST(Contains2, OperationsNegative)
{
    EXPECT_FALSE((Contains2<Derived<boost::mpl::vector<Transition<_, e, _> > >, Action, Guard, e_>::value));
}

} // namespace UT
} // namespace Aux
} // namespace Back
} // namespace QFsm

