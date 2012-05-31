//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_OPERATIONS_AND_HPP
#define QFSM_FRONT_OPERATIONS_AND_HPP

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include "QFsm/Back/Aux/Operation.hpp"
#include "QFsm/Back/Aux/Call.hpp"

namespace QFsm
{
namespace Front
{
namespace Operations
{

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_PP_SUB(QFSM_OPERATION_LIMIT_SIZE, 1))
#define QFSM_AND_CALL_IMPL(z, n, TCall) BOOST_PP_IF(n, BOOST_PP_IDENTITY(&&), BOOST_PP_EMPTY)() TCall<bool, Guard##n>::execute(p_event, p_pool, p_callBack)
#define QFSM_AND_PRINT_IMPL(z, n, text) BOOST_PP_COMMA_IF(n) None
#define QFSM_AND_ACTION_DEFAULT_IMPL(z, n, text) BOOST_PP_COMMA_IF(n) text##n = None

template<BOOST_PP_REPEAT(QFSM_OPERATION_LIMIT_SIZE, QFSM_AND_ACTION_DEFAULT_IMPL, typename Guard), template<typename, typename> class TCall = Back::Aux::Call>
class And : public BOOST_PP_CAT(Back::Aux::Operation, QFSM_OPERATION_LIMIT_SIZE)<BOOST_PP_ENUM_PARAMS(QFSM_OPERATION_LIMIT_SIZE, Guard)>
{
public:
    template<typename Event, typename Pool, typename CallBack>
    bool operator()(const Event& p_event, Pool& p_pool, const CallBack& p_callBack) const
    {
        return BOOST_PP_REPEAT(QFSM_OPERATION_LIMIT_SIZE, QFSM_AND_CALL_IMPL, TCall);
    }
};

#define BOOST_PP_LOCAL_MACRO(n)\
    template<BOOST_PP_ENUM_PARAMS(n, typename Guard), template<typename, typename> class TCall = Back::Aux::Call>\
    class And<BOOST_PP_ENUM_PARAMS(n, Guard), BOOST_PP_REPEAT(BOOST_PP_SUB(QFSM_OPERATION_LIMIT_SIZE, n), QFSM_AND_PRINT_IMPL, None)>\
        : public BOOST_PP_CAT(Back::Aux::Operation, n)<BOOST_PP_ENUM_PARAMS(n, Guard), TCall>\
    {\
    public:\
        template<typename Event, typename Pool, typename CallBack>\
        bool operator()(const Event& p_event, Pool& p_pool, const CallBack& p_callBack) const\
        {\
            return BOOST_PP_REPEAT(n, QFSM_AND_CALL_IMPL, TCall);\
        }\
    };

#   include BOOST_PP_LOCAL_ITERATE()
#   undef OPERATION

#undef QFSM_AND_CALL_IMPL
#undef QFSM_AND_PRINT_IMPL
#undef QFSM_AND_ACTION_DEFAULT_IMPL

} // namespace Operations
} // namespace Front
} // namespace QFsm

#endif

