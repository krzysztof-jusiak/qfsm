//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include "QFsm/Aux/TypeTraits/HasCallOperator.hpp"

namespace QFsm
{
namespace Aux
{
namespace TypeTraits
{
namespace UT
{

class T1 { };

class T2
{
public:
    bool operator()(int) { return false;}
};

class T3
{
public:
    void operator()(int) { }
};

class T4
{
public:
    bool operator()(int);
};

class T5
{
public:
    bool operator()(int) const { return false; }
};

class T6
{
public:
    bool operator()(const int&) const { return false; }
};

TEST(HasCallOperator, Types)
{
    EXPECT_FALSE((HasCallOperator<T1, bool(const int&)>::value));
    EXPECT_FALSE((HasCallOperator<T3, bool(const int&)>::value));
    EXPECT_TRUE ((HasCallOperator<T2, bool(const int&)>::value));
    EXPECT_TRUE ((HasCallOperator<T4, bool(const int&)>::value));
    EXPECT_TRUE ((HasCallOperator<T5, bool(const int&)>::value));
    EXPECT_TRUE ((HasCallOperator<T6, bool(const int&)>::value));
}

} // namespace UT
} // namespace TypeTraits
} // namespace Aux
} // namespace QFsm

