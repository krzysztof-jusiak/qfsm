//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <QFsm/QFsm.hpp>
#include "Utility.hpp"

class FavorPolicy : public QFsm::Fsm
{
    struct S1 { };
    struct S2 { };

public:
    typedef QFsm::TransitionTable
    <
        Transition < S1,     e1,     S2 >,
        Transition < S2,     e2,     S1 >
    >
    TransitionTable;
};

int main()
{
    {
        QFsm::Front::Fsm<FavorPolicy, QFsm::Back::FavorExecutionSpeed> fsm;

        fsm.processEvent(e1());
        fsm.visitCurrentStates(ShowCurrentStateVisitor());

        fsm.processEvent(e2());
        fsm.visitCurrentStates(ShowCurrentStateVisitor());
    }

    {
        QFsm::Front::Fsm<FavorPolicy, QFsm::Back::FavorCompilationTime> fsm;

        fsm.processEvent(e1());
        fsm.visitCurrentStates(ShowCurrentStateVisitor());

        fsm.processEvent(e2());
        fsm.visitCurrentStates(ShowCurrentStateVisitor());
    }

    return 0;
}

