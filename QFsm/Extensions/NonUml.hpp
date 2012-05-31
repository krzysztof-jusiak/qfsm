//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_EXTENSIONS_NONUML_HPP
#define QFSM_EXTENSIONS_NONUML_HPP

/**
 * @Note: this file has to be included before fsm front
 *
 * Finish
 *     struct Composite : public QFsm::Front::Fsm
 *     {
 *          typedef boost::mpl::vector<S1, S4> InitialState;
 *
 *          typedef boost::mpl::vector
 *          <
 *              Transition < S1 , e1 , Finish >
 *             ,Transition < S4 , e2 , Finish >
 *          >
 *          TransitionTable;
 *     };
 *
 *     struct StateMachine : public QFsm::Front::Fsm<StateMachine>
 *     {
 *          typedef boost::mpl::vector
 *          <
 *              Transition < S1        , e3 , Composite , None                  >
 *             ,Transition < Composite , _  , S2        , IsFinal<Composite>    >
 *          >
 *          TransitionTable;
 *     };
 *
 * Interrupt states
 *     Transition < S1 , e1 , Interrupt<e3> >
 *
 * Else
 *     Transition < S1 , e1   , S2        >
 *    ,Transition < S1 , Else , Terminate >
 *
 * All events history
 *     struct Fsm : public QFsm::Front::Fsm
 *     {
 *          typedef boost::mpl::vector
 *          <
 *              Transition < S1 , e1 , S2 >
 *          >
 *          TransitionTable;
 *
 *          typedef Back::AllEventsHistory History; //Fsm will be reactivated in last state in case when any event will be received
 *     };
 *
 *  On Exception
 *      Transition < S1, OnException<std::out_of_range>, S2 >
 *
 */

#define QFSM_EXTENSIONS_NON_UML

#include "QFsm/Front/Operations/Interrupt.hpp"
#include "QFsm/Front/Operations/Else.hpp"

#endif

