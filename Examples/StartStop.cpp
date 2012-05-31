//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <QFsm/QFsm.hpp>
#include "Utility.hpp"

class StartStop : public QFsm::Fsm
{
    struct S1 { };
    struct S2 { };
    struct S3 { };

public:
    typedef QFsm::TransitionTable
    <
        Transition < S1 , _ ,  S2 >,
        Transition < S2 , e1 , S3 >
    >
    TransitionTable;
};

int main()
{
    QFsm::Front::Fsm<StartStop> fsm;

    fsm.start(); //completion transition to S2
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.processEvent(e1()); //S2->S3
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.stop();
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    try
    {
        fsm.processEvent(e1()); //not handled
    }
    catch(...)
    {
        std::cout << "unhandled e1" << std::endl;
    }

    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.start(); //not possible

    return 0;
}

