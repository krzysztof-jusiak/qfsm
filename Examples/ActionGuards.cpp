//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <QFsm/QFsm.hpp>
#include "Utility.hpp"

struct A1
{
    template<typename Event> void operator()(const Event&)
    {
        std::cout << "A1" << std::endl;
    }
};

struct EntryAction
{
    template<typename Event> void operator()(const Event&)
    {
        std::cout << "EntryAction" << std::endl;
    }
};


class A2
{
public:
    explicit A2(const std::string& p_name)
        : m_name(p_name)
    { }

    template<typename Event> void operator()(const Event&)
    {
        std::cout << m_name << std::endl;
    }

private:
    std::string m_name;
};

struct G1
{
    template<typename Event> bool operator()(const Event&) const
    {
        std::cout << "G1" << std::endl;
        return true;
    }
};

struct G2
{
    explicit G2(const std::string& p_name)
        : m_name(p_name)
    { }

    template<typename Event> bool operator()(const Event&) const
    {
        std::cout << m_name << std::endl;
        return true;
    }

private:
    std::string m_name;
};

struct G3
{
    template<typename Event> bool operator()(const Event&) const
    {
        std::cout << "G3" << std::endl;
        return false;
    }
};

class ActionGuards : public QFsm::Fsm
{
    class S1 { };
    class S2 { };
    class S3 { };
    class S4 { };

public:
    typedef QFsm::TransitionTable
    <
        Transition < S1 , e1        , S2 ,  A1 ,           G1           >,
        Transition < S1 , e1        , S2 ,  A1 ,           G1           >,
        Transition < S2 , e2        , S3 ,  A2 ,           And<G1, G2>  >,
        Transition < S3 , e3        , _ ,   Seq<A1, A2> ,  _            >,
        Transition < S3 , e4        , S4 ,  _ ,            G3           >
    >
    TransitionTable;
};

int main()
{
    QFsm::Front::Fsm<ActionGuards> fsm
    (
        //NOTE order in ctor is not important

        boost::make_shared<A2>("A2 - external"),
        boost::make_shared<G2>("G2 - external")
    );

    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.processEvent(e1());
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.processEvent(e2());
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    fsm.processEvent(e3());
    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    try
    {
        fsm.processEvent(e4());
    }
    catch(...)
    {
        std::cout << "unhandled e4" << std::endl;
    }

    fsm.visitCurrentStates(ShowCurrentStateVisitor());

    return 0;
}

