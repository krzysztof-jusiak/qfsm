//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_IACTION_HPP
#define QFSM_FRONT_IACTION_HPP

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/mpl/limits/vector.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/assert.hpp>
#include "QFsm/Front/Operations/None.hpp"

namespace QFsm
{
namespace Front
{

namespace Detail
{

BOOST_MPL_HAS_XXX_TRAIT_DEF(first)
BOOST_MPL_HAS_XXX_TRAIT_DEF(second)
BOOST_MPL_HAS_XXX_TRAIT_DEF(element_type)

template<typename TEvent, typename Enable = void>
class IAction
{
public:
    virtual ~IAction() { }
    virtual void operator()(const TEvent& p_event) = 0;
};

template<typename TEvent>
class IAction<TEvent, typename boost::enable_if<boost::mpl::and_< has_first<TEvent>, has_second<TEvent> > >::type>
{
    typedef typename TEvent::first Event;
    typedef typename TEvent::second ReturnType;

    BOOST_MPL_ASSERT_MSG(
        (has_element_type<ReturnType>::value),
        RETURN_TYPE_HAS_TO_BE_A_SMART_PTR,
        (ReturnType)
    );

public:
    virtual ~IAction() { }
    virtual ReturnType operator()(const Event& p_event) = 0;
};
} // namespace Detail

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_PP_SUB(BOOST_MPL_LIMIT_VECTOR_SIZE, 1))
#define QFSM_IACTION_IMPL(z, n, text) BOOST_PP_COMMA_IF(n) text##n = Operations::None
#define QFSM_IACTION_INHERITANCE_IMPL(z, n, text) BOOST_PP_COMMA_IF(n) public Detail::IAction<text##n>
#define QFSM_IACTION_PRINT_IMPL(z, n, text) BOOST_PP_COMMA_IF(n) Operations::None

/**
 * Action interface
 *
 * @code
 * class MyAction1 : public QFsm::Front::IAction<e1>
 * {
 * public:
 *     void operator()(const e1&) { }
 * };
 *
 * class MyAction2 : public QFsm::Front::IAction<e1, e2>
 * {
 * public:
 *     void operator()(const e1&) { }
 *     void operator()(const e2&) { }
 * };
 *
 * class MyAction3 : public QFsm::Front::IAction<e1, e2, boost::mpl::pair<e3, boost::shared_ptr<i1> > >
 * {
 * public:
 *     void operator()(const e1&) { }
 *     void operator()(const e2&) { }
 *     boost::shared_ptr<i1> operator()(const e3&) { return boost::make_shared<i1>(); }
 * };
 * @endcode
 */
template<BOOST_PP_REPEAT(BOOST_MPL_LIMIT_VECTOR_SIZE, QFSM_IACTION_IMPL, typename Event)> class IAction;

#define BOOST_PP_LOCAL_MACRO(n)                                                                                                                                 \
    template<BOOST_PP_ENUM_PARAMS(n, typename Event)>                                                                                                           \
    class IAction<BOOST_PP_ENUM_PARAMS(n, Event), BOOST_PP_REPEAT(BOOST_PP_SUB(BOOST_MPL_LIMIT_VECTOR_SIZE, n), QFSM_IACTION_PRINT_IMPL, Operations::None)>     \
        : BOOST_PP_REPEAT(n, QFSM_IACTION_INHERITANCE_IMPL, Event)                                                                                              \
    { };

#include BOOST_PP_LOCAL_ITERATE()

#undef QFSM_IACTION_IMPL
#undef QFSM_IACTION_INHERITANCE_IMPL
#undef QFSM_IACTION_PRINT_IMPL

} // namespace Front
} // namespace QFsm

#endif

