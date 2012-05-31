//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <QFsm/QFsm.hpp>
#include "Utility.hpp"

class Show
{
public:
    template<typename Event> void operator()(const Event&)
    {
        std::cout << "Handle deferral event" << std::endl;
    }
};

class Deferral : public QFsm::Fsm
{
    class S1 { };
    class S2 { };
    class S3 { };

public:
    typedef QFsm::TransitionTable
    <
        Transition < S1 , e1, S2, Defer >,
        Transition < S2 , e2, S3, _     >,
        Transition < S3 , e1, _,  Show  >
    >
    TransitionTable;
};

int main()
{
    QFsm::Front::Fsm<Deferral> fsm;
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.processEvent(e1());
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.processEvent(e2());
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    return 0;
}

