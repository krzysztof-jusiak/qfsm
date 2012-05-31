//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <QFsm/QFsm.hpp>
#include <QFsm/Utility/Dispatcher.hpp>
#include "Utility.hpp"

const int Event1Id = 1;
const int Event2Id = 2;

struct Event1 { static const int value = Event1Id; Event1(const int&) { } };
struct Event2 { static const int value = Event2Id; Event2(const int&) { } };

class Player : public QFsm::Fsm
{
    struct State1 { };
    struct State2 { };

public:
    typedef QFsm::TransitionTable
    <
        Transition < State1, Event1, State2 >,
        Transition < State2, Event2, State1 >
    >
    TransitionTable;
};

int main()
{
    QFsm::Utility::Dispatcher<> dispatcher;
    QFsm::Front::Fsm<Player> fsm;
    dispatcher.registerHandler(fsm);

    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    assert(dispatcher.dispatch(boost::make_shared<int>(Event1Id)));
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    assert(dispatcher.dispatch(boost::make_shared<int>(Event2Id)));
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    assert(!dispatcher.dispatch(boost::make_shared<int>(42)));

    return 0;
}

