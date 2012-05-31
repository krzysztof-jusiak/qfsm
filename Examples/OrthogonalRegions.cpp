//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <QFsm/QFsm.hpp>
#include "Utility.hpp"

class OrthogonalRegions : public QFsm::Fsm
{
    class S1 { };
    class S2 { };
    class S3 { };
    class S4 { };

public:
    typedef QFsm::InitialState<S1, S3> InitialState; // 2 orthogonal regions

    typedef QFsm::TransitionTable
    <
        Transition < S1, e1, S2 >,
        Transition < S2, e2, S1 >,

        Transition < S3, e1, S4 >,
        Transition < S4, e2, S3 >
    >
    TransitionTable;
};

int main()
{
    QFsm::Front::Fsm<OrthogonalRegions> fsm;

    fsm.start();
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.processEvent(e1());
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.processEvent(e2());
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.processEvent(e1());
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.processEvent(e2());
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    return 0;
}

