//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include <boost/type_traits/is_same.hpp>
#include "QFsm/Back/Policy.hpp"

namespace QFsm
{
namespace Back
{
namespace UT
{

TEST(Policy, FavorCompilationTime)
{
    EXPECT_TRUE((boost::is_same<FavorCompilationTime<>::Orthogonality, void>::value));
    EXPECT_TRUE((boost::is_same<FavorCompilationTime<>::Cache, void>::value));
    EXPECT_TRUE((boost::is_same<FavorCompilationTime<CacheEnabled>::Orthogonality, void>::value));
    EXPECT_TRUE((boost::is_same<FavorCompilationTime<CacheEnabled>::Cache, CacheEnabled>::value));
    EXPECT_TRUE((boost::is_same<FavorCompilationTime<CacheEnabled, CheckOrthogonality>::Orthogonality, CheckOrthogonality>::value));
    EXPECT_TRUE((boost::is_same<FavorCompilationTime<CacheEnabled, CheckOrthogonality>::Cache, CacheEnabled>::value));
    EXPECT_TRUE((boost::is_same<FavorCompilationTime<CheckOrthogonality>::Orthogonality, CheckOrthogonality>::value));
    EXPECT_TRUE((boost::is_same<FavorCompilationTime<CheckOrthogonality>::Cache, void>::value));
    EXPECT_TRUE((boost::is_same<FavorCompilationTime<CheckOrthogonality, CacheEnabled>::Orthogonality, CheckOrthogonality>::value));
    EXPECT_TRUE((boost::is_same<FavorCompilationTime<CheckOrthogonality, CacheEnabled>::Cache, CacheEnabled>::value));
}

TEST(Policy, FavorExecutionSpeed)
{
    EXPECT_TRUE((boost::is_same<FavorExecutionSpeed<>::Orthogonality, void>::value));
    EXPECT_TRUE((boost::is_same<FavorExecutionSpeed<>::Cache, CacheEnabled>::value));
    EXPECT_TRUE((boost::is_same<FavorExecutionSpeed<CacheEnabled>::Orthogonality, void>::value));
    EXPECT_TRUE((boost::is_same<FavorExecutionSpeed<CacheEnabled>::Cache, CacheEnabled>::value));
    EXPECT_TRUE((boost::is_same<FavorExecutionSpeed<CacheEnabled, CheckOrthogonality>::Orthogonality, CheckOrthogonality>::value));
    EXPECT_TRUE((boost::is_same<FavorExecutionSpeed<CacheEnabled, CheckOrthogonality>::Cache, CacheEnabled>::value));
    EXPECT_TRUE((boost::is_same<FavorExecutionSpeed<CheckOrthogonality>::Orthogonality, CheckOrthogonality>::value));
    EXPECT_TRUE((boost::is_same<FavorExecutionSpeed<CheckOrthogonality>::Cache, CacheEnabled>::value));
    EXPECT_TRUE((boost::is_same<FavorExecutionSpeed<CheckOrthogonality, CacheEnabled>::Orthogonality, CheckOrthogonality>::value));
    EXPECT_TRUE((boost::is_same<FavorExecutionSpeed<CheckOrthogonality, CacheEnabled>::Cache, CacheEnabled>::value));
}

TEST(Policy, FavorDebugSize)
{
    EXPECT_TRUE((boost::is_same<FavorDebugSize<>::Orthogonality, void>::value));
    EXPECT_TRUE((boost::is_same<FavorDebugSize<>::Cache, void>::value));
    EXPECT_TRUE((boost::is_same<FavorDebugSize<CacheEnabled>::Orthogonality, void>::value));
    EXPECT_TRUE((boost::is_same<FavorDebugSize<CacheEnabled>::Cache, CacheEnabled>::value));
    EXPECT_TRUE((boost::is_same<FavorDebugSize<CacheEnabled, CheckOrthogonality>::Orthogonality, CheckOrthogonality>::value));
    EXPECT_TRUE((boost::is_same<FavorDebugSize<CacheEnabled, CheckOrthogonality>::Cache, CacheEnabled>::value));
    EXPECT_TRUE((boost::is_same<FavorDebugSize<CheckOrthogonality>::Orthogonality, CheckOrthogonality>::value));
    EXPECT_TRUE((boost::is_same<FavorDebugSize<CheckOrthogonality>::Cache, void>::value));
    EXPECT_TRUE((boost::is_same<FavorDebugSize<CheckOrthogonality, CacheEnabled>::Orthogonality, CheckOrthogonality>::value));
    EXPECT_TRUE((boost::is_same<FavorDebugSize<CheckOrthogonality, CacheEnabled>::Cache, CacheEnabled>::value));
}

} // namespace UT
} // namespace Back
} // namespace QFsm

