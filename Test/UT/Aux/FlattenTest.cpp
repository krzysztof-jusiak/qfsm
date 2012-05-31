//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/equal.hpp>
#include "QFsm/Aux/Flatten.hpp"

namespace QFsm
{
namespace Aux
{
namespace UT
{

TEST(Flatten, Basic)
{
    EXPECT_TRUE((
        boost::mpl::equal
        <
            boost::mpl::vector<int>,
            Flatten< boost::mpl::vector< boost::mpl::vector<int> > >::type
        >::value
    ));
}

TEST(Flatten, ManyElements)
{
    EXPECT_TRUE((
        boost::mpl::equal
        <
            boost::mpl::vector<int, double, float>,
            Flatten< boost::mpl::vector< boost::mpl::vector<int, double>, boost::mpl::vector<float> > >::type
        >::value
    ));
}

TEST(Flatten, NotTheSame)
{
    EXPECT_FALSE((
        boost::mpl::equal
        <
            boost::mpl::vector<int, float>,
            Flatten< boost::mpl::vector< boost::mpl::vector<int, double>, boost::mpl::vector<float> > >::type
        >::value
    ));
}

TEST(Flatten, Order)
{
    EXPECT_FALSE((
        boost::mpl::equal
        <
            boost::mpl::vector<int, float, double>,
            Flatten< boost::mpl::vector< boost::mpl::vector<int, double>, boost::mpl::vector<float> > >::type
        >::value
    ));
}

TEST(Flatten, NoSeq)
{
    EXPECT_FALSE((
        boost::mpl::equal
        <
            boost::mpl::vector<int>,
            Flatten<int>::type
        >::value
    ));
}

TEST(Flatten, ManyLevels)
{
    EXPECT_TRUE((
        boost::mpl::equal
        <
            boost::mpl::vector<int, double>,
            Flatten< boost::mpl::vector<boost::mpl::vector<int>, double> >::type
        >::value
    ));
}

} // namespace UT
} // namespace Aux
} // namespace QFsm

