//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_BASE_FSM_HPP
#define QFSM_FRONT_BASE_FSM_HPP

#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/if.hpp>
#include "QFsm/Back/Policy.hpp"
#include "QFsm/Back/Logger.hpp"
#include "QFsm/Back/UnexpectedEvent.hpp"
#include "QFsm/Back/FsmFavor.hpp"
#include "QFsm/Front/Fsm.hpp"
#include "QFsm/Back/Aux/Detail/Pool/Pool.hpp"
#include "QFsm/Back/Aux/Detail/Ctor.hpp"
#include "QFsm/Front/Base/Detail/Keys.hpp"

namespace QFsm
{
namespace Front
{

namespace Detail
{

template
<
    typename TTransitionTable,
    typename TInitialState,
    typename TUnexpectedEvent,
    typename TLogger
>
class Derived
{
public:
    typedef TTransitionTable TransitionTable;
    typedef TInitialState InitialState;
    typedef TUnexpectedEvent UnexpectedEvent;
    typedef TLogger Logger;
};

template<typename TPolicy>
struct BasePolicy : boost::mpl::if_
    <
        boost::is_same<TPolicy, boost::mpl::_1>,
        QFSM_FSM_DEFAULT_POLICY,
        TPolicy
    >
{ };

} // namespace Detail

template
<
    typename T0,
    typename T1 = boost::mpl::_1,
    typename T2 = QFSM_DEFAULT_UNEXPECTED_EVENT,
    typename T3 = QFSM_DEFAULT_LOGGER,
    typename T4 = QFSM_FSM_DEFAULT_POLICY,
    typename Enable = void
>
class Fsm;

template
<
    typename TDerived,
    typename TPolicy
>
class Fsm<TDerived, TPolicy, QFSM_DEFAULT_UNEXPECTED_EVENT/*not used*/, QFSM_DEFAULT_LOGGER/*not used*/, QFSM_FSM_DEFAULT_POLICY/*not used*/, typename boost::disable_if<boost::mpl::is_sequence<TDerived> >::type>
    : public Back::FsmFavor<TDerived, Back::Aux::Detail::Pool::Pool<typename Detail::Keys<typename TDerived::TransitionTable, typename TDerived::UnexpectedEvent, typename TDerived::Logger>::type>, typename Detail::BasePolicy<TPolicy>::type>
{
    typedef Back::FsmFavor<TDerived, Back::Aux::Detail::Pool::Pool<typename Detail::Keys<typename TDerived::TransitionTable, typename TDerived::UnexpectedEvent, typename TDerived::Logger>::type>, typename Detail::BasePolicy<TPolicy>::type> Base;

public:
    CTOR_REF(Fsm, Base, { })
};

template
<
    typename TTransitionTable,
    typename TInitialState,
    typename TUnexpectedEvent,
    typename TLogger,
    typename TPolicy
>
class Fsm<TTransitionTable, TInitialState, TUnexpectedEvent, TLogger, TPolicy, typename boost::enable_if<boost::mpl::is_sequence<TTransitionTable> >::type>
    : public Back::FsmFavor<Detail::Derived<TTransitionTable, TInitialState, TUnexpectedEvent, TLogger>, Back::Aux::Detail::Pool::Pool<typename Detail::Keys<TTransitionTable, TUnexpectedEvent, TLogger>::type>, TPolicy>
{
    typedef Back::FsmFavor<Detail::Derived<TTransitionTable, TInitialState, TUnexpectedEvent, TLogger>, Back::Aux::Detail::Pool::Pool<typename Detail::Keys<TTransitionTable, TUnexpectedEvent, TLogger>::type>, TPolicy> Base;

public:
    CTOR_REF(Fsm, Base, { })
};

} // namespace Front
} // namespace QFsm

#undef QFSM_EXTENSIONS_UML
#undef QFSM_EXTENSIONS_NON_UML

#endif

