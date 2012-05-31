//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_DETAIL_RESULTOF_HPP
#define QFSM_BACK_AUX_DETAIL_RESULTOF_HPP

#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#ifndef RESULT_OF_LIMIT_SIZE
# define RESULT_OF_LIMIT_SIZE 5
#endif

namespace QFsm
{
namespace Back
{
namespace Aux
{
namespace Detail
{

/**
 * helper class to identify result type without decltype
 *
 * @code
 * QFsm::Back::Aux::Detail::ResultOf<int (*)(int)>::type result_type; // -> int
 * @endcode
 */
template<typename> struct ResultOf;

#define RESULT_OF_IMPL(z, n, text)\
    template<typename Ret BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, typename T)> struct ResultOf<Ret (*)(BOOST_PP_ENUM_PARAMS(n, T))> { typedef Ret type; };

#define RESULT_OF_MEMBER_IMPL(z, n, text)\
    template<typename Ret, typename Base BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, typename T)> struct ResultOf<Ret (Base::*)(BOOST_PP_ENUM_PARAMS(n, T))> { typedef Ret type; };

BOOST_PP_REPEAT(RESULT_OF_LIMIT_SIZE, RESULT_OF_IMPL, ~)
BOOST_PP_REPEAT(RESULT_OF_LIMIT_SIZE, RESULT_OF_MEMBER_IMPL, ~)

#undef RESULT_OF_IMPL
#undef RESULT_OF_MEMBER_IMPL

} // namespace Detail
} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

