//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_EXTENSIONS_UML_HPP
#define QFSM_EXTENSIONS_UML_HPP

/**
 * @Note: this file has to be included before fsm front
 *
 * Entry action
 *     Transition < S1 , OnEntry , _ , Action1 >
 *
 * Exit action
 *     Transition <S1 , OnExit , _ , Action1 >
 *
 * Event deferral
 *     Transition < S1 , e1 , S2 , Defer >
 *
 * Internal transitions (none entry/exit action)
 *     Transition < S1 , e1 , _ , Action1 >
 *
 * Internal events
 *     Transition < S1 , e1 , SendInternalEvent<e2, Action1> >
 *
 * Completion/Anonymous transitions
 *     Transition < S1 , _ , S2 >
 *    ,Transition < S2 , _ , S3 >
 *
 * Terminate states
 *     Transition < S1 , e1 , Terminate >
 *
 * Composite/Hierarchically nested states
 *     Transition < S1  , e1 , Fsm >
 *    ,Transition < Fsm , e2 , S2  >
 *
 * Orthogonal regions
 *     typedef boost::mpl::vector<S1, S5> InitialState;
 *
 * Deep/Shallow history
 *     struct StateMachine : public QFsm::Front::Fsm
 *     {
 *          typedef boost::mpl::vector
 *          <
 *              Transition < S1 , e1 , S2 >
 *          >
 *          TransitionTable;
 *
 *          typedef ShallowHistory<e1> History; //Fsm will be reactivated in last state in case when 'e1' will be received
 *          //typedef NoHistory History; //no shallow history
 *     };
 *
 * Super State
 *     struct SuperState
 *     {
 *         typedef boost::mpl::vector
 *         <
 *             Transition < _1 , e1 , S2 >
 *         >
 *         TransitionTable;
 *     };
 */

#define QFSM_EXTENSIONS_UML

#include "QFsm/Front/Operations/OnExit.hpp"
#include "QFsm/Front/Operations/Terminate.hpp"
#include "QFsm/Front/Operations/Defer.hpp"
#include "QFsm/Front/Operations/SendInternalEvent.hpp"

#endif

