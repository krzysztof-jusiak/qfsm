//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_DETAIL_POOL_PUSHBACK_HPP
#define QFSM_BACK_AUX_DETAIL_POOL_PUSHBACK_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/mpl/limits/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/push_back.hpp>
#include "QFsm/Back/Aux/Detail/Pool/Pool.hpp"

namespace QFsm
{
namespace Back
{
namespace Aux
{
namespace Detail
{
namespace Pool
{

template<typename TPool, typename T>
typename TPool::template PoolType<typename boost::mpl::push_back<typename TPool::type, typename boost::mpl::if_< has_element_type<T>, T, ElementType<T> >::type::element_type>::type>::type pushBack(TPool&, T& p_el, typename boost::enable_if_c<boost::mpl::size<typename TPool::type>::value == 0>::type* = 0)
{
    return typename TPool::template PoolType<typename boost::mpl::push_back<typename TPool::type, typename boost::mpl::if_< has_element_type<T>, T, ElementType<T> >::type::element_type >::type>::type(p_el);
}

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_MPL_LIMIT_VECTOR_SIZE)
#define PUSH_BACK_MEMBER_IMPL(z, n, pool) BOOST_PP_COMMA_IF(n) l_##n
#define PUSH_BACK_LOCAL_MEMBER_IMPL(z, n, pool) BOOST_AUTO(l_##n, (pool.template get<typename boost::mpl::at_c<typename TPool::type, n>::type>()));

#define BOOST_PP_LOCAL_MACRO(n)\
     template<typename TPool, typename T>\
     typename TPool::template PoolType<typename boost::mpl::push_back<typename TPool::type, typename boost::mpl::if_< has_element_type<T>, T, ElementType<T> >::type::element_type>::type>::type pushBack(TPool& p_pool, T& p_el, typename boost::enable_if_c<boost::mpl::size<typename TPool::type>::value == n>::type* = 0)\
     {\
         BOOST_PP_REPEAT(n, PUSH_BACK_LOCAL_MEMBER_IMPL, p_pool)\
         return typename TPool::template PoolType<typename boost::mpl::push_back<typename TPool::type, typename boost::mpl::if_< has_element_type<T>, T, ElementType<T> >::type::element_type >::type>::type(BOOST_PP_REPEAT(n, PUSH_BACK_MEMBER_IMPL, ~), p_el);\
     }

#include BOOST_PP_LOCAL_ITERATE()
#undef PUSH_BACK_MEMBER_IMPL

} // namespace Pool
} // namespace Detail
} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

