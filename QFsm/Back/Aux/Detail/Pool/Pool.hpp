//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_DETAIL_POOL_HPP
#define QFSM_BACK_AUX_DETAIL_POOL_HPP

#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/mpl/limits/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/has_xxx.hpp>
#include "QFsm/Back/Aux/Detail/Pool/Member.hpp"

#ifndef QFSM_DEFAULT_POOL_ALLOCATOR
# define QFSM_DEFAULT_POOL_ALLOCATOR boost::shared_ptr
#endif

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

BOOST_MPL_HAS_XXX_TRAIT_DEF(element_type)

template<typename T> struct ElementType
{
    typedef T element_type;
};

template<typename TSeq, template<typename> class TAllocator = QFSM_DEFAULT_POOL_ALLOCATOR, std::size_t = boost::mpl::size<TSeq>::value> class Pool
{
public:
    typedef TSeq type;
    template<typename Seq = TSeq, template<typename> class Allocator = TAllocator> struct PoolType { typedef Pool<Seq, Allocator> type; };
};

#if __GNUC__ >= 4
# pragma GCC diagnostic ignored "-Wreorder"
#endif

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_MPL_LIMIT_VECTOR_SIZE)
#define POOL_MEMBER(z, n, access) BOOST_PP_COMMA_IF(n) access Member< TAllocator<typename boost::mpl::at_c<typename TSeq::type, n>::type> >
#define POOL_CTOR(z, n, name) template<BOOST_PP_ENUM_PARAMS(n, typename T)> name(BOOST_PP_REPEAT(n, POOL_CTOR_IMPL, T)) : BOOST_PP_REPEAT(n, POOL_INITLIST, ~) { }
#define POOL_CTOR_IMPL(z, n, name) BOOST_PP_COMMA_IF(n) name##n p_arg##n
#define POOL_INITLIST(z, n, not_used) BOOST_PP_COMMA_IF(n) Member< TAllocator<typename boost::mpl::if_< has_element_type<T##n>, T##n, ElementType<T##n> >::type::element_type> >(p_arg##n)

#define BOOST_PP_LOCAL_MACRO(n)\
     template<typename TSeq, template<typename> class TAllocator> class Pool<TSeq, TAllocator, n> : BOOST_PP_REPEAT(n, POOL_MEMBER, private)\
     {\
     public:\
         typedef TSeq type;\
         template<typename Seq = TSeq, template<typename> class Allocator = TAllocator> struct PoolType { typedef Pool<Seq, Allocator> type; };\
\
         Pool() { }\
         BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_ADD(n, 1), POOL_CTOR, Pool)\
\
         template<typename T> void set(T p_new) { Member<T>::set(p_new); }\
         template<typename T> typename Member< TAllocator<T> >::type get() { return Member< TAllocator<T> >::get(); }\
         template<typename T> T& acquire() { return Member< TAllocator<T> >::acquire(); }\
     };

#include BOOST_PP_LOCAL_ITERATE()

#undef POOL_MEMBER
#undef POOL_CTOR
#undef POOL_CTOR_IMPL
#undef POOL_INITLIST

} // namespace Pool
} // namespace Detail
} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

