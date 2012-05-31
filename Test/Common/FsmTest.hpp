//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_TEST_COMMON_FSMTEST_HPP
#define QFSM_TEST_COMMON_FSMTEST_HPP

#include "gtest/gtest.h"
#include <boost/mpl/empty.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/front.hpp>
#include <boost/shared_ptr.hpp>
#include "Common/FsmTypes.hpp"
#include "QFsm/Front/Fusion/Fsm.hpp"

#ifdef __GNUC__
# pragma GCC system_header
#endif

namespace QFsm
{
namespace Test
{
namespace Common
{

namespace Detail
{
template
<
    typename TInitialState,
    typename TTransitionTable
>
struct TransitionTable
{
    typedef TTransitionTable type;
    typedef TInitialState InitialState;
    typedef QFsm::Aux::Pool::Pool< boost::mpl::vector0<> > Pool;
};
} // namespace Detail

#define FSM_TEST(name, ...)\
    template<typename Fsm> class name : public ::testing::Test\
    {\
    public:\
        name()\
            : m_fsm(new Fsm)\
        { }\
    \
        boost::shared_ptr<Fsm> m_fsm;\
    };\
    \
    template\
    <\
        typename TInitialState,\
        typename TTransitionTable,\
        typename TUnexpectedEvent,\
        typename TLogger,\
        typename TPolicy\
    >\
    class name< Fusion<TInitialState, TTransitionTable, TUnexpectedEvent, TLogger, TPolicy> > : public ::testing::Test\
    {\
    public:\
        name()\
        {\
            BOOST_AUTO(l_transitionTable, QFsm::Front::Fusion::TransitionTable<TInitialState>());\
            fillTransitions<TTransitionTable>(l_transitionTable);\
        }\
    \
    private:\
        template<typename Seq, typename T> void fillTransitions(T p_transitionTable, typename boost::enable_if< boost::mpl::empty<Seq> >::type* = 0)\
        {\
            m_fsm.reset(reinterpret_cast<QFsm::Front::Fusion::Fsm<QFsm::Test::Common::Detail::TransitionTable<TInitialState, TTransitionTable>, TUnexpectedEvent, TLogger, TPolicy>*>(new QFsm::Front::Fusion::Fsm<BOOST_TYPEOF(p_transitionTable), TUnexpectedEvent, TLogger, TPolicy>(p_transitionTable)));\
        }\
        template<typename Seq, typename T> void fillTransitions(T p_transitionTable, typename boost::disable_if< boost::mpl::empty<Seq> >::type* = 0)\
        {\
            typedef typename boost::mpl::front<Seq>::type Current;\
            fillTransitions<typename boost::mpl::pop_front<Seq>::type>(p_transitionTable.transition(typename Current::StateInit(), QFsm::Front::Fusion::Event<typename Current::Event>(), typename Current::StateTarget()));\
        }\
    \
    public:\
        boost::shared_ptr< QFsm::Front::Fusion::Fsm<QFsm::Test::Common::Detail::TransitionTable<TInitialState, TTransitionTable>, TUnexpectedEvent, TLogger, TPolicy> > m_fsm;\
    };\
    \
    typedef FsmTypes<__VA_ARGS__>::type FsmTestTypes##name;\
    \
    TYPED_TEST_CASE(name, FsmTestTypes##name)

} // namespace Common
} // namespace Test
} // namespace QFsm

#endif

