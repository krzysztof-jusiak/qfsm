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

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_PP_SUB(QFSM_OPERATION_LIMIT_SIZE, 1))
#define QFSM_SEQ_CALL_IMPL(z, n, TCall) TCall<void, Action##n>::execute(p_event, p_pool, p_callBack);
#define QFSM_SEQ_PRINT_IMPL(z, n, text) BOOST_PP_COMMA_IF(n) None
#define QFSM_SEQ_ACTION_DEFAULT_IMPL(z, n, text) BOOST_PP_COMMA_IF(n) text##n = None

template<BOOST_PP_REPEAT(QFSM_OPERATION_LIMIT_SIZE, QFSM_SEQ_ACTION_DEFAULT_IMPL, typename Action), template<typename, typename> class TCall = Back::Aux::Call>
class Seq : public BOOST_PP_CAT(Back::Aux::Operation, QFSM_OPERATION_LIMIT_SIZE)<BOOST_PP_ENUM_PARAMS(QFSM_OPERATION_LIMIT_SIZE, Action)>
{
public:
    template<typename Event, typename Pool, typename CallBack>
    void operator()(const Event& p_event, Pool& p_pool, const CallBack& p_callBack) const
    {
        BOOST_PP_REPEAT(QFSM_OPERATION_LIMIT_SIZE, QFSM_SEQ_CALL_IMPL, TCall)
    }
};

#define BOOST_PP_LOCAL_MACRO(n)\
    template<BOOST_PP_ENUM_PARAMS(n, typename Action)>\
    class Seq<BOOST_PP_ENUM_PARAMS(n, Action), BOOST_PP_REPEAT(BOOST_PP_SUB(QFSM_OPERATION_LIMIT_SIZE, n), QFSM_SEQ_PRINT_IMPL, None), template<typename, typename> class TCall = Back::Aux::Call>\
        : public BOOST_PP_CAT(Back::Aux::Operation, n)<BOOST_PP_ENUM_PARAMS(n, Action), TCall>\
    {\
    public:\
        template<typename Event, typename Pool, typename CallBack>\
        void operator()(const Event& p_event, Pool& p_pool, const CallBack& p_callBack) const\
        {\
            BOOST_PP_REPEAT(n, QFSM_SEQ_CALL_IMPL, TCall)\
        }\
    };

#   include BOOST_PP_LOCAL_ITERATE()
#   undef OPERATION

#undef QFSM_SEQ_CALL_IMPL
#undef QFSM_SEQ_PRINT_IMPL
#undef QFSM_SEQ_ACTION_DEFAULT_IMPL

} // namespace Operations
} // namespace Front
} // namespace QFsm

#endif

