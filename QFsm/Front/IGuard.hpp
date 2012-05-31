//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_IGUARD_HPP
#define QFSM_FRONT_IGUARD_HPP

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/fusion/container/vector/limits.hpp>
#include "QFsm/Front/Operations/None.hpp"

namespace QFsm
{
namespace Front
{

namespace Detail
{

/**
 * [Not mandatory] Guard interface
 */
template<typename TEvent>
class IGuard
{
public:
    virtual ~IGuard() { }
    virtual bool operator()(const TEvent&) = 0;
};

} // namespace Detail

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_PP_SUB(FUSION_MAX_VECTOR_SIZE, 1))
#define IGUARD_IMPL(z, n, text) BOOST_PP_COMMA_IF(n) text##n = Operations::None
#define IGUARD_INHERITANCE_IMPL(z, n, text) BOOST_PP_COMMA_IF(n) public Detail::IGuard<text##n>
#define IGUARD_PRINT_IMPL(z, n, text) BOOST_PP_COMMA_IF(n) Operations::None

template<BOOST_PP_REPEAT(FUSION_MAX_VECTOR_SIZE, IGUARD_IMPL, typename Event)> class IGuard;

#define BOOST_PP_LOCAL_MACRO(n)\
    template<BOOST_PP_ENUM_PARAMS(n, typename Event)>\
    class IGuard<BOOST_PP_ENUM_PARAMS(n, Event), BOOST_PP_REPEAT(BOOST_PP_SUB(FUSION_MAX_VECTOR_SIZE, n), IGUARD_PRINT_IMPL, Operations::None)> : BOOST_PP_REPEAT(n, IGUARD_INHERITANCE_IMPL, Event)\
    { };

#include BOOST_PP_LOCAL_ITERATE()

#undef IGUARD_IMPL
#undef IGUARD_INHERITANCE_IMPL
#undef IGUARD_PRINT_IMPL

} // namespace Front
} // namespace QFsm

#endif

