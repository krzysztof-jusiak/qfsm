//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_OPERATIONS_TRANSITION_HPP
#define QFSM_FRONT_OPERATIONS_TRANSITION_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include "QFsm/Aux/TypeTraits/HasCallOperator.hpp"
#include "QFsm/Back/Aux/Extensions.hpp"
#include "QFsm/Front/Operations/OnEntry.hpp"
#include "QFsm/Front/Operations/OnExit.hpp"
#include "QFsm/Front/Operations/None.hpp"
#include "QFsm/Front/Operations/Terminate.hpp"
#include "QFsm/Front/Operations/Interrupt.hpp"

namespace QFsm
{
namespace Front
{
namespace Operations
{

namespace Detail { class Transition_ { }; } // namespace Detail

/**
 * @code
 * class Fsm : public QFsm::Front::Fsm
 * {
 *     struct S1 { };
 *     struct S2 { };
 *     struct S3 { };
 *
 *     typedef boost::mpl::vector
 *     <
 *         Transition < S1 , e1 , S2 , Action ,  Guard  >,
 *         Transition < S2 , e2 , S3 , Guard            >,
 *         Transition < S2 , e2 , S3 , Guard ,   Action >,
 *         Transition < S2 , e2 , S3 , Action           >,
 *         Transition < S2 , e2 , S3 , _,        Guard  >
 *     >
 *     TransitionTable;
 * };
 * @endcode
 *
 * @tparam TStateInit init state
 * @tparam TEvent event
 * @tparam TStateTarget target state
 * @tparam TAction action
 * @tparam TGuard guard
 */
template<typename TStateInit, typename TEvent, typename TStateTarget, typename TAction, typename TGuard>
class TransitionImpl : Detail::Transition_
{
    QFSM_UML_EXTENSIONS(
        BOOST_MPL_ASSERT_MSG(
            (
                boost::mpl::if_
                <
                    boost::mpl::or_
                    <
                        boost::is_same<TEvent, OnEntry>,
                        boost::is_same<TEvent, OnExit>
                    >,
                    boost::is_same<TStateTarget, None>,
                    boost::mpl::true_
                >::type::value
            ),
            StateTransitionNotAllowedDuringOperation,
            (TEvent)
        );
    )

    QFSM_UML_EXTENSIONS(
        BOOST_MPL_ASSERT_MSG(
            (
                !boost::is_base_of<Terminate, TStateInit>::value
            ),
            StateTransitionNotAllowedFromTerminatedState,
            (TStateInit)
        );
    )

    QFSM_NON_UML_EXTENSIONS(
        BOOST_MPL_ASSERT_MSG(
            (
                !boost::is_base_of<Interrupt_, TStateInit>::value
            ),
            StateTransitionNotAllowedFromInterruptedState,
            (TStateInit)
        );
    )

public:
    typedef TStateInit StateInit;
    typedef TEvent Event;
    typedef TStateTarget StateTarget;
    typedef TAction Action;
    typedef TGuard Guard;
};

#if __GNUC_ >= 4
template<typename, typename, typename, typename = None, typename = None, typename Enable = void> class Transition;

template<typename TStateInit, typename TEvent, typename TStateTarget, typename TAction, typename TGuard>
class Transition<TStateInit, TEvent, TStateTarget, TAction, TGuard, typename boost::disable_if< Aux::TypeTraits::HasCallOperator<TAction, bool(const TEvent&)> >::type>
    : public TransitionImpl<TStateInit, TEvent, TStateTarget, TAction, TGuard>
{ };

template<typename TStateInit, typename TEvent, typename TStateTarget, typename TGuard, typename TAction>
class Transition<TStateInit, TEvent, TStateTarget, TAction, TGuard, typename boost::enable_if< Aux::TypeTraits::HasCallOperator<TGuard, bool(const TEvent&)> >::type>
    : public TransitionImpl<TStateInit, TEvent, TStateTarget, TAction, TGuard>
{ };

template<typename TStateInit, typename TEvent, typename TStateTarget, typename TGuard>
class Transition<TStateInit, TEvent, TStateTarget, None, TGuard, typename boost::enable_if< Aux::TypeTraits::HasCallOperator<TGuard, bool(const TEvent&)> >::type>
    : public TransitionImpl<TStateInit, TEvent, TStateTarget, None, TGuard>
{ };

template<typename TStateInit, typename TEvent, typename TStateTarget, typename TAction>
class Transition<TStateInit, TEvent, TStateTarget, TAction, None, typename boost::disable_if< Aux::TypeTraits::HasCallOperator<TAction, bool(const TEvent&)> >::type>
    : public TransitionImpl<TStateInit, TEvent, TStateTarget, TAction, None>
{ };
#else
template<typename TStateInit, typename TEvent, typename TStateTarget, typename TAction = None, typename TGuard = None>
class Transition : public TransitionImpl<TStateInit, TEvent, TStateTarget, TAction, TGuard>
{ };
#endif

} // namespace Operations
} // namespace Front
} // namespace QFsm

#endif

