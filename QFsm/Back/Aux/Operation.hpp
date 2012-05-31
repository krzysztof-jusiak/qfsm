//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_OPERATION_HPP
#define QFSM_BACK_AUX_OPERATION_HPP

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/mpl/vector.hpp>
#include "QFsm/Back/Aux/Internal.hpp"

#ifndef OPERATION_LIMIT_SIZE
# define OPERATION_LIMIT_SIZE 5
#endif

namespace QFsm
{
namespace Back
{
namespace Aux
{

/**
 * Helpful class to identify operation
 */
class Operation : Internal { };

namespace Detail
{
template<typename T, bool = false> struct If { typedef T type; };
template<typename T> struct If<T, true> { typedef typename T::type type; };
} // namespace Detail

#define BOOST_PP_LOCAL_LIMITS (1, OPERATION_LIMIT_SIZE)
#define OPERATION(z, n, text) BOOST_PP_COMMA_IF(n) typename Detail::If<T##n, boost::is_base_of<Back::Aux::Operation, T##n>::value>::type

#define BOOST_PP_LOCAL_MACRO(n)\
    template <BOOST_PP_ENUM_PARAMS(n, typename T)> struct Operation##n : Back::Aux::Operation, boost::mpl::vector##n\
        <\
            BOOST_PP_REPEAT(n, OPERATION, ~)\
        >\
    { };

#   include BOOST_PP_LOCAL_ITERATE()
#   undef OPERATION

} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

