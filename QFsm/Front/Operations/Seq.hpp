//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_OPERATIONS_SEQ_HPP
#define QFSM_FRONT_OPERATIONS_SEQ_HPP

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/cat.hpp>
#include "QFsm/Front/Operations/None.hpp"
#include "QFsm/Back/Aux/Operation.hpp"
#include "QFsm/Back/Aux/Call.hpp"

namespace QFsm
{
namespace Front
{
namespace Operations
{

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_PP_SUB(OPERATION_LIMIT_SIZE, 1))
#define SEQ_CALL_IMPL(z, n, text) Back::Aux::Call<void, Action##n>::execute(p_event, p_fsm);
#define SEQ_PRINT_IMPL(z, n, text) BOOST_PP_COMMA_IF(n) None
#define SEQ_ACTION_DEFAULT_IMPL(z, n, text) BOOST_PP_COMMA_IF(n) text##n = None

template<BOOST_PP_REPEAT(OPERATION_LIMIT_SIZE, SEQ_ACTION_DEFAULT_IMPL, typename Action)> class Seq
    : public BOOST_PP_CAT(Back::Aux::Operation, OPERATION_LIMIT_SIZE)<BOOST_PP_ENUM_PARAMS(OPERATION_LIMIT_SIZE, Action)>
{
public:
    template<typename TFsm, typename TEvent> void operator()(const TEvent& p_event, TFsm& p_fsm) const
    {
        BOOST_PP_REPEAT(OPERATION_LIMIT_SIZE, SEQ_CALL_IMPL, ~)
    }
};

#define BOOST_PP_LOCAL_MACRO(n)\
    template<BOOST_PP_ENUM_PARAMS(n, typename Action)> class Seq<BOOST_PP_ENUM_PARAMS(n, Action), BOOST_PP_REPEAT(BOOST_PP_SUB(OPERATION_LIMIT_SIZE, n), SEQ_PRINT_IMPL, None)>\
        : public BOOST_PP_CAT(Back::Aux::Operation, n)<BOOST_PP_ENUM_PARAMS(n, Action)>\
    {\
    public:\
        template<typename TFsm, typename TEvent> void operator()(const TEvent& p_event, TFsm& p_fsm) const\
        {\
            BOOST_PP_REPEAT(n, SEQ_CALL_IMPL, ~)\
        }\
    };

#   include BOOST_PP_LOCAL_ITERATE()
#   undef OPERATION

#undef SEQ_CALL_IMPL
#undef SEQ_PRINT_IMPL
#undef SEQ_ACTION_DEFAULT_IMPL

} // namespace Operations
} // namespace Front
} // namespace QFsm

#endif

