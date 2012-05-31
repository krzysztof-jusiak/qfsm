//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include "QFsm/Aux/Ctor.hpp"

namespace QFsm
{
namespace Aux
{
namespace UT
{

class Base0Mock
{
public:
    Base0Mock() { }
};

template<int expected>
class Base1Mock
{
public:
    Base1Mock(int p_1)
    {
        EXPECT_EQ(expected, p_1);
    }
};

template<int expected1, int expected2, int expected3>
class Base3Mock
{
public:
    Base3Mock(int p_1, int p_2, int p_3)
    {
        EXPECT_EQ(expected1, p_1);
        EXPECT_EQ(expected2, p_2);
        EXPECT_EQ(expected3, p_3);
    }
};

template<typename TBase>
class Constructor : public TBase
{
public:
    CTOR_REF(Constructor, TBase,
        {
            calls()++;
        }
    )

    static int& calls()
    {
        static int s_calls = 0;
        return s_calls;
    }
};

TEST(Ctor, Default)
{
    //given
    typedef Constructor<Base0Mock> Ctor;
    Ctor::calls() = 0;

    //when
    Ctor l_ctor;

    //then
    EXPECT_EQ(1, Ctor::calls());
}

TEST(Ctor, OneParameter)
{
    //given
    const int l_expected1 = 0;
    typedef Constructor< Base1Mock<l_expected1> > Ctor;
    Ctor::calls() = 0;

    //when
    Ctor l_ctor(l_expected1);

    //then
    EXPECT_EQ(1, Ctor::calls());
}

TEST(Ctor, ManyParameters)
{
    //given
    const int l_expected1 = 0;
    const int l_expected2 = 1;
    const int l_expected3 = 1;
    typedef Constructor< Base3Mock<l_expected1, l_expected2, l_expected3> > Ctor;
    Ctor::calls() = 0;

    //when
    Ctor l_ctor(l_expected1, l_expected2, l_expected3);

    //then
    EXPECT_EQ(1, Ctor::calls());
}

} // namespace UT
} // namespace Aux
} // namespace QFsm

