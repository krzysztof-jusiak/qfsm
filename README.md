Quick Finite State Machine (QFsm)
================================

## Introduction
QFsm is proof-of-concept, header only library implementing Finite State Machine concept.

### Hello World
struct Guard {
    template<typename TEvent>
    bool operator()(const TEvent&) const { return true; }
};

struct Action {
    template<typename TEvent>
    void operator()(const TEvent&) const { }
};

struct event1 { };
struct event2 { };

class ActionGuards : public QFsm::Fsm
{
    class State1 { };
    class State2 { };

public:
    typedef QFsm::TransitionTable<
        Transition < State1 , event1 , State2 ,  Action , Guard >
      , Transition < State2 , event2 , State1 ,  Action , _     >
    > TransitionTable;
};

int main() {
    QFsm::Front::Fsm<ActionGuards> fsm(
        //NOTE order in ctor is not important
        boost::make_shared<Action>(),
        boost::make_shared<Guard>()
    );

    fsm.processEvent(event1());
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.processEvent(event1());
    fsm.visitCurrentStates(ShowCurrentStateVisitor());
}

## Papers
 * [https://docs.google.com/viewer?url=https%3A%2F%2Fgithub.com%2Fkrzysztof-jusiak%2Fdoc%2Fblob%2Fmaster%2Ffsms%2Fdoc%2Ffsms.pdf%3Fraw%3Dtrue](C++ Finite-state machine frameworks comparison)
 * [https://docs.google.com/viewer?url=https%3A%2F%2Fgithub.com%2Fkrzysztof-jusiak%2Fdoc%2Fblob%2Fmaster%2Fdispatchers%2Fdoc%2Fdispatchers.pdf%3Fraw%3Dtrue](C++ dispatching concepts comparison)

## Key features
* Header only
* Type safe
* Performance - compile time approach
* UML compliant

## License
Distributed under the [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt).

