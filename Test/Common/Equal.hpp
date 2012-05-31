//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_TEST_COMMON_EQUAL_HPP
#define QFSM_TEST_COMMON_EQUAL_HPP

#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/utility/enable_if.hpp>

namespace QFsm
{
namespace Test
{
namespace Common
{

template<typename T1, typename T2, typename Enable = void> class Equal
{
    struct ContainsAll : boost::mpl::fold
        <
            T1,
            boost::mpl::vector0<>,
            boost::mpl::if_
            <
                boost::mpl::contains<T2, boost::mpl::_2>,
                boost::mpl::_1,
                boost::mpl::push_back<boost::mpl::_1, boost::mpl::_2>
            >
        >::type
    { };

    BOOST_MPL_ASSERT_MSG(
        boost::mpl::size<ContainsAll>::value == 0,
        TypesAreNotEqual,
        (typename ContainsAll::type)
    );

public:
    static const bool value = boost::mpl::size<ContainsAll>::value == 0;
};

template<typename T1, typename T2>
class Equal<T1, T2, typename boost::enable_if< boost::mpl::not_equal_to< boost::mpl::size<T1>, boost::mpl::size<T2> > >::type> : public boost::mpl::false_
{
    BOOST_MPL_ASSERT_MSG(
        false,
        TypesAreNotEqualDueToDifferentSizes,
        (typename boost::mpl::size<T1>::type, typename boost::mpl::size<T2>::type)
    );
};

} // namespace Common
} // namespace Test
} // namespace QFsm

#endif

