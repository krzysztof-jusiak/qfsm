//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_FUSION_TRANSITIONTABLE_HPP
#define QFSM_FRONT_FUSION_TRANSITIONTABLE_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_back.hpp>
#include "QFsm/Aux/Pool/Pool.hpp"
#include "QFsm/Aux/Pool/PushBack.hpp"
#include "QFsm/Front/Operations/None.hpp"
#include "QFsm/Front/Operations/Transition.hpp"
#include "QFsm/Front/Fusion/Event.hpp"
#include "QFsm/Front/Fusion/Detail/GuardProxy.hpp"
#include "QFsm/Front/Fusion/Detail/ActionProxy.hpp"
#include "QFsm/Front/Fusion/Detail/CompositeProxy.hpp"

namespace QFsm
{
namespace Front
{
namespace Fusion
{

template
<
    typename TInitialState = boost::mpl::_1,
    typename THistory = boost::mpl::vector0<>,
    typename TTransitionTable = boost::mpl::vector0<>,
    typename TPool = QFsm::Aux::Pool::Pool< boost::mpl::vector0<> >
>
class TransitionTable
{
public:
    typedef TTransitionTable type;
    typedef TInitialState InitialState;
    typedef TPool Pool;

   explicit TransitionTable(const TPool& p_pool = TPool())
        : m_pool(p_pool)
    { }

    template<typename TStateInit, typename TEvent, typename TStateTarget> TransitionTable
    <
        InitialState,
        typename boost::mpl::push_back
        <
            TTransitionTable,
            Operations::Transition
            <
                TStateInit, TEvent, TStateTarget,
                Detail::ActionProxy<typename boost::mpl::size<TTransitionTable>::type, TEvent>,
                Detail::GuardProxy<typename boost::mpl::size<TTransitionTable>::type, TEvent>
            >
        >::type,
        QFsm::Aux::Pool::Pool
        <
            typename boost::mpl::push_back
            <
                typename boost::mpl::push_back
                <
                    typename TPool::type,
                    Detail::ActionProxy<typename boost::mpl::size<TTransitionTable>::type, TEvent>
                >::type,
                Detail::GuardProxy<typename boost::mpl::size<TTransitionTable>::type, TEvent>
            >::type
        >
    >
    transition(const TStateInit&, Event<TEvent> p_event, const TStateTarget&)
    {
        typedef boost::shared_ptr< Detail::ActionProxy<typename boost::mpl::size<TTransitionTable>::type, TEvent> > Action;
        typedef boost::shared_ptr< Detail::GuardProxy<typename boost::mpl::size<TTransitionTable>::type, TEvent> > Guard;
        typedef typename QFsm::Aux::Pool::Pool<typename boost::mpl::push_back<typename TPool::type, typename Action::value_type>::type> Pool1;
        typedef typename QFsm::Aux::Pool::Pool<typename boost::mpl::push_back<typename boost::mpl::push_back<typename TPool::type, typename Action::value_type>::type, typename Guard::value_type>::type> Pool2;

        Action l_action(new typename Action::value_type(p_event.action()));
        Guard l_guard(new typename Guard::value_type(p_event.guard()));

        Pool1 l_pool1 = QFsm::Aux::Pool::pushBack(m_pool, l_action);
        Pool2 l_pool = QFsm::Aux::Pool::pushBack(l_pool1, l_guard);

        TransitionTable
        <
            InitialState,
            typename boost::mpl::push_back
            <
                TTransitionTable,
                Operations::Transition<TStateInit, TEvent, TStateTarget, typename Action::value_type, typename Guard::value_type>
            >::type,
            Pool2
        >
        l_table(l_pool);

        return l_table;
    }

#if 0
    template<typename TStateInit, typename TEvent> TransitionTable
    <
        InitialState,
        typename boost::mpl::push_back
        <
            TTransitionTable,
            Operations::Transition
            <
                TStateInit, TEvent, Operations::None,
                Detail::ActionProxy<typename boost::mpl::size<TTransitionTable>::type, TEvent>,
                Detail::GuardProxy<typename boost::mpl::size<TTransitionTable>::type, TEvent>
            >
        >::type,
        typename boost::fusion::result_of::push_back
        <
            const typename boost::fusion::result_of::push_back
            <
                const TPool,
                boost::shared_ptr< Detail::ActionProxy<typename boost::mpl::size<TTransitionTable>::type, TEvent> >
            >::type,
            boost::shared_ptr< Detail::GuardProxy<typename boost::mpl::size<TTransitionTable>::type, TEvent> >
        >::type
    >
    transition(const TStateInit&, Event<TEvent> p_event)
    {
        return transition<TStateInit, TEvent, Operations::None>(TStateInit(), p_event, Operations::None());
    }
#endif

    TPool& pool() { return m_pool; }

private:
    TPool m_pool;
};

} // namespace Front
} // namespace Fusion
} // namespace QFsm

#endif

