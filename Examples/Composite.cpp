//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <QFsm/QFsm.hpp>
#include "Utility.hpp"

class A
{
public:
    template<typename Event> void operator()(const Event&)
    {
        std::cout << "SubFsm Action" << std::endl;
    }
};

class Composite : public QFsm::Fsm
{
    class S1 { };
    class S2 { };

    class SubComposite : public QFsm::Fsm
    {
        class S3 { };
        class S4 { };

    public:
        typedef QFsm::TransitionTable
        <
            Transition < S3 , e0 , S4, A >
        >
        TransitionTable;
    };

    typedef QFsm::Front::Fsm<SubComposite> SubFsm;

public:
    typedef QFsm::TransitionTable
    <
        Transition < S1      , e1 , S2      >,
        Transition < S2      , e2 , SubFsm  >,
        Transition < SubFsm  , e3,  S1      >
    >
    TransitionTable;
};

int main()
{
    QFsm::Front::Fsm<Composite> fsm;
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.processEvent(e1());
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.processEvent(e2());
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.processEvent(e0()); // handled by SubFsm
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.processEvent(e3()); // exit from SubFsm
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    return 0;
}

