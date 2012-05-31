//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_TEST_COMMON_FSMTYPES_HPP
#define QFSM_TEST_COMMON_FSMTYPES_HPP

#include "gtest/gtest.h"
#include "QFsm/Extensions/Uml.hpp"
#include "QFsm/Extensions/NonUml.hpp"
#include "QFsm/Front/Default/Fsm.hpp"
#include "QFsm/Front/Fusion/Fsm.hpp"

namespace QFsm
{
namespace Test
{
namespace Common
{

template
<
    typename TInitialState,
    typename TTransitionTable,
    typename TUnexpectedEvent,
    typename TLogger
>
class Fsm
{
public:
    class type : public Front::Fsm<type>
    {
    public:
        typedef TInitialState InitialState;
        typedef TTransitionTable TransitionTable;
        typedef TUnexpectedEvent UnexpectedEvent;
        typedef TLogger Logger;
    };
};

template
<
    typename TInitialState,
    typename TTransitionTable,
    typename TUnexpectedEvent,
    typename TLogger,
    typename TPolicy
>
struct Fusion
{
    typedef TInitialState InitialState;
    typedef TTransitionTable TransitionTable;
    typedef TUnexpectedEvent UnexpectedEvent;
    typedef TLogger Logger;
    typedef TPolicy Policy;
};

template
<
    typename TInitialState,
    typename TTransitionTable,
    typename TUnexpectedEvent,
    typename TLogger
>
struct FsmTypes
{
    typedef ::testing::Types
    <
        //Fusion<TInitialState, TTransitionTable, TUnexpectedEvent, TLogger, QFsm::Back::FavorDebugSize>,
        //Fusion<TInitialState, TTransitionTable, TUnexpectedEvent, TLogger, QFsm::Back::FavorCompilationTime>,
        //Fusion<TInitialState, TTransitionTable, TUnexpectedEvent, TLogger, QFsm::Back::FavorExecutionSpeed>,
        Front::Default::Fsm<typename Fsm<TInitialState, TTransitionTable, TUnexpectedEvent, TLogger>::type, QFsm::Back::FavorDebugSize<> >,
        Front::Default::Fsm<typename Fsm<TInitialState, TTransitionTable, TUnexpectedEvent, TLogger>::type, QFsm::Back::FavorCompilationTime<> >,
        Front::Default::Fsm<typename Fsm<TInitialState, TTransitionTable, TUnexpectedEvent, TLogger>::type, QFsm::Back::FavorExecutionSpeed<> >,
        Front::Default::Fsm<TTransitionTable, TInitialState, TUnexpectedEvent, TLogger, QFsm::Back::FavorDebugSize<> >,
        Front::Default::Fsm<TTransitionTable, TInitialState, TUnexpectedEvent, TLogger, QFsm::Back::FavorCompilationTime<> >,
        Front::Default::Fsm<TTransitionTable, TInitialState, TUnexpectedEvent, TLogger, QFsm::Back::FavorExecutionSpeed<> >
    >
    type;
};

} // namespace Common
} // namespace Test
} // namespace QFsm

#endif

