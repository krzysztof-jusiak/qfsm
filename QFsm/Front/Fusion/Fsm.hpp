//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_FUSION_FSM_HPP
#define QFSM_FRONT_FUSION_FSM_HPP

#if 0
#include <boost/typeof/typeof.hpp>
#include <boost/utility/base_from_member.hpp>
#include "QFsm/Aux/Pool/Pool.hpp"
#include "QFsm/Aux/Pool/PushBack.hpp"
#include "QFsm/Back/FsmFavor.hpp"
#include "QFsm/Back/Policy.hpp"
#include "QFsm/Front/Fusion/Detail/TransitionTable.hpp"

namespace QFsm
{
namespace Front
{
namespace Fusion
{

namespace Detail
{

template
<
    typename TTransitionTable,
    typename TInitialState,
    typename TUnexpectedEvent,
    typename TLogger
>
class Derived
{
public:
    typedef TTransitionTable TransitionTable;
    typedef TInitialState InitialState;
    typedef TUnexpectedEvent UnexpectedEvent;
    typedef TLogger Logger;
};

template
<
    typename TPool,
    typename TUnexpectedEvent,
    typename TLogger
>
class PoolHelper
{
    typedef Aux::Pool::Pool
    <
        typename boost::mpl::push_back
        <
            typename boost::mpl::push_back
            <
                typename TPool::type,
                TUnexpectedEvent
            >::type,
            TLogger
        >::type
    > Pool_;

    typedef TPool& Pool;

    static TUnexpectedEvent& unexpectedEvent()
    {
        static TUnexpectedEvent s_unexpectedEvent = TUnexpectedEvent(new typename TUnexpectedEvent::value_type);
        return s_unexpectedEvent;
    }

    static TLogger& logger()
    {
        static TLogger s_logger = TLogger(new typename TLogger::value_type);
        return s_logger;
    }

public:
    typedef Pool type;

    explicit PoolHelper(TPool& p_pool)
        : m_pool(p_pool)
    { }

/*    explicit PoolHelper(TPool& p_pool, TUnexpectedEvent p_unexpectedEvent)*/
        //: m_pool(Aux::pushBack(Aux::pushBack(p_pool, p_unexpectedEvent), logger()))
    //{ }

    //explicit PoolHelper(TPool& p_pool, TLogger p_logger)
        //: m_pool(Aux::pushBack(Aux::pushBack(p_pool, unexpectedEvent()), p_logger))
    //{ }

    //explicit PoolHelper(TPool& p_pool, TUnexpectedEvent p_unexpectedEvent, TLogger p_logger)
        //: m_pool(Aux::pushBack(Aux::pushBack(p_pool, p_unexpectedEvent), p_logger))
    /*{ }*/

    Pool pool() { return m_pool; }

private:
    Pool m_pool;
};

} // namespace Detail

/**
 * @code
 *    BOOST_AUTO(l_transitionTable, (
 *       TransitionTable<S1>()
 *           .transition(S1(), Event<e1>(guard) / action, S2())
 *           .transition(S2(), Event<e2>(guard), S3())
 *           .transition(S3(), Event<e3>(), S4())
 *           .transition(S4(), Event<e4>() / action)
 *   ));
 *
 *   QFsm::Front::Fusion::Fsm<BOOST_TYPEOF(l_transitionTable)> l_fsm(l_transitionTable);
 *
 * @endcode
 */
template
<
    typename TTransitionTable,
    typename TUnexpectedEvent = QFSM_DEFAULT_UNEXPECTED_EVENT,
    typename TLogger = QFSM_DEFAULT_LOGGER,
    typename TPolicy = QFSM_DEFAULT_POLICY
>
class Fsm : private Detail::PoolHelper
            <
                typename TTransitionTable::Pool,
                TUnexpectedEvent,
                TLogger
            >,

            public Back::FsmFavor
            <
                Detail::Derived
                <
                    typename TTransitionTable::type,
                    typename TTransitionTable::InitialState,
                    TUnexpectedEvent,
                    TLogger
                >,
                typename Detail::PoolHelper
                <
                    typename TTransitionTable::Pool,
                    TUnexpectedEvent,
                    TLogger
                >::type,
                TPolicy
            >
{
    typedef Detail::PoolHelper<typename TTransitionTable::Pool, TUnexpectedEvent, TLogger> PoolHelperType;

public:
    explicit Fsm(TTransitionTable& p_transitionTable)
        : PoolHelperType(p_transitionTable.pool()),
          Back::FsmFavor<Detail::Derived<typename TTransitionTable::type, typename TTransitionTable::InitialState, TUnexpectedEvent, TLogger>, typename PoolHelperType::type, TPolicy>(PoolHelperType::pool())
    { }

/*    explicit Fsm(TTransitionTable& p_transitionTable, UnexpectedEventType p_unexpectedEvent)*/
        //: PoolHelperType(p_transitionTable.pool()),
          //Back::FsmFavor<Detail::Derived<typename TTransitionTable::type, typename TTransitionTable::InitialState, TUnexpectedEvent, TLogger>, typename PoolHelperType::type, TPolicy>(PoolHelperType::pool(), p_unexpectedEvent)
    //{ }

    //explicit Fsm(TTransitionTable& p_transitionTable, LoggerType p_logger)
        //: PoolHelperType(p_transitionTable.pool()),
          //Back::FsmFavor<Detail::Derived<typename TTransitionTable::type, typename TTransitionTable::InitialState, TUnexpectedEvent, TLogger>, typename PoolHelperType::type, TPolicy>(PoolHelperType::pool(), p_logger)
    //{ }

    //explicit Fsm(TTransitionTable& p_transitionTable, UnexpectedEventType p_unexpectedEvent, LoggerType p_logger)
        //: PoolHelperType(p_transitionTable.pool()),
          //Back::FsmFavor<Detail::Derived<typename TTransitionTable::type, typename TTransitionTable::InitialState, TUnexpectedEvent, TLogger>, typename PoolHelperType::type, TPolicy>(PoolHelperType::pool(), p_unexpectedEvent, p_logger)
    //{ }

    //explicit Fsm(TTransitionTable& p_transitionTable, LoggerType p_logger, UnexpectedEventType p_unexpectedEvent)
        //: PoolHelperType(p_transitionTable.pool()),
          //Back::FsmFavor<Detail::Derived<typename TTransitionTable::type, typename TTransitionTable::InitialState, TUnexpectedEvent, TLogger>, typename PoolHelperType::type, TPolicy>(PoolHelperType::pool(), p_unexpectedEvent, p_logger)
    /*{ }*/
};

} // namespace Front
} // namespace Fusion
} // namespace QFsm

#undef QFSM_EXTENSIONS_UML
#undef QFSM_EXTENSIONS_NON_UML

#endif

#endif

