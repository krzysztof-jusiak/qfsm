//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_OPERATIONS_HISTORY_HPP
#define QFSM_FRONT_OPERATIONS_HISTORY_HPP

#include <boost/config.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/mpl/limits/vector.hpp>
#include <boost/mpl/vector.hpp>
#include "QFsm/Back/Aux/Internal.hpp"
#include "QFsm/Back/Aux/Extensions.hpp"

namespace QFsm
{
namespace Front
{
namespace Operations
{

namespace Detail
{
class History_ : Back::Aux::Internal { };
} // namespace Detail

class NoHistory : Detail::History_ { };

QFSM_NON_UML_EXTENSIONS (
    class AllEventsHistory : Detail::History_ { };
)

#if defined(BOOST_HAS_VARIADIC_TMPL)
    QFSM_UML_EXTENSIONS (
        template<typename... T> class ShallowHistory : Detail::History, public boost::mpl::vector<T...>
        { };
    )
#else
    template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_MPL_LIMIT_VECTOR_SIZE, typename T, boost::mpl::void_)>
    class ShallowHistory : Detail::History_, public BOOST_PP_CAT(boost::mpl::vector, BOOST_MPL_LIMIT_VECTOR_SIZE)<BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_VECTOR_SIZE, T) >
    { };
#endif

} // namespace Operations
} // namespace Front
} // namespace QFsm

#endif

