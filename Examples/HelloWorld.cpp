//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <QFsm/QFsm.hpp>
#include "Utility.hpp"

class HelloWorld : public QFsm::Fsm
{
    class S1 { };
    class S2 { };

public:
    typedef QFsm::TransitionTable
    <
        Transition < S1 , e1, S2 >
    >
    TransitionTable;
};

int main()
{
    QFsm::Front::Fsm<HelloWorld> fsm;
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.processEvent(e1());
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    try
    {
        fsm.processEvent(e1());  //unexpected event
    }
    catch(...)
    {
        std::cout << "unhandled e1" << std::endl;
    }

    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    return 0;
}

