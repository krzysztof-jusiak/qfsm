//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_DETAIL_CTOR_HPP
#define QFSM_BACK_AUX_DETAIL_CTOR_HPP

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/mpl/limits/vector.hpp>

#ifdef __GNUC__
# pragma GCC system_header
#endif

#define SEQ_VARIADIC_ELEM(seq) SEQ_ELEM_0 seq
#define SEQ_ELEM_0(...) SEQ_ELEM_1
#define SEQ_ELEM_1(...) SEQ_ELEM_2
#define SEQ_ELEM_2(...) __VA_ARGS__
#define PARAMS_IMPL(z, n, param) BOOST_PP_COMMA_IF(n) param##n p_##n
#define BASE_PARAMS_IMPL(z, n, param) BOOST_PP_COMMA_IF(n) p_##n

#define CTOR_REF_IMPL(z, n, ctor)\
    template<BOOST_PP_ENUM_PARAMS(n, typename T)> BOOST_PP_SEQ_ELEM(0, ctor)\
    (BOOST_PP_REPEAT(n, PARAMS_IMPL, T))\
        : BOOST_PP_SEQ_ELEM(1, ctor)(BOOST_PP_REPEAT(n, BASE_PARAMS_IMPL, T))\
    SEQ_VARIADIC_ELEM(ctor)

#define CTOR_REF(Class, Base, ...)\
    Class() __VA_ARGS__\
    BOOST_PP_REPEAT_FROM_TO(1, BOOST_MPL_LIMIT_VECTOR_SIZE, CTOR_REF_IMPL, (Class)(Base)(__VA_ARGS__))

#endif

