//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_COMPOSITEHISTORY_HPP
#define QFSM_BACK_DETAIL_COMPOSITEHISTORY_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/contains.hpp>
#include "QFsm/Back/Aux/Composite.hpp"
#include "QFsm/Back/Aux/TransitionTypes.hpp"
#include "QFsm/Front/Operations/History.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{

namespace Detail
{

template<typename TPool>
class CompositeInitStartVisitor
{
public:
    explicit CompositeInitStartVisitor(TPool& p_pool)
        : m_pool(p_pool)
    { }

    template<typename Composite>
    void operator()(typename boost::enable_if< boost::is_base_of<Aux::Composite, Composite> >::type* = 0) const
    {
        QFSM_TRACE("composite history [%s]", typeid(Composite).name());
        (m_pool.template acquire<Composite>()).init();
        (m_pool.template acquire<Composite>()).start();
    }

    template<typename Composite>
    void operator()(typename boost::disable_if< boost::is_base_of<Aux::Composite, Composite> >::type* = 0) const
    { }

private:
    TPool& m_pool;
};

template<typename TPool>
class CompositeStartVisitor
{
public:
    explicit CompositeStartVisitor(TPool& p_pool)
        : m_pool(p_pool)
    { }

    template<typename Composite>
    void operator()(typename boost::enable_if< boost::is_base_of<Aux::Composite, Composite> >::type* = 0) const
    {
        QFSM_TRACE("composite history [%s]", typeid(Composite).name());
        (m_pool.template acquire<Composite>()).start();
    }

    template<typename Composite>
    void operator()(typename boost::disable_if< boost::is_base_of<Aux::Composite, Composite> >::type* = 0) const
    { }

private:
    TPool& m_pool;
};

} // namespace Detail

template<typename THistory, typename TVisitor, typename Enable = void> class CompositeHistory
{
public:
    template<typename Event, typename State, typename Pool>
    static void execute(const State& p_currentState, const State& p_newState, Pool& p_pool)
    {
        if (p_currentState != p_newState)
        {
            TVisitor::execute(p_newState, Detail::CompositeStartVisitor<Pool>(p_pool));
        }
    }
};

template<typename THistory, typename TVisitor>
class CompositeHistory<THistory, TVisitor, typename boost::enable_if<boost::is_same<THistory, Front::Operations::AllEventsHistory> >::type>
{
public:
    template<typename Event, typename State, typename Pool>
    static void execute(const State& p_currentState, const State& p_newState, Pool& p_pool)
    {
        if (p_currentState != p_newState)
        {
            TVisitor::execute(p_newState, Detail::CompositeInitStartVisitor<Pool>(p_pool));
        }
    }
};

template<typename THistory, typename TVisitor>
class CompositeHistory<THistory, TVisitor, typename boost::enable_if<boost::mpl::is_sequence<THistory> >::type>
{
public:
    template<typename Event, typename State, typename Pool>
    static void execute(const State& p_currentState, const State& p_newState, Pool& p_pool, typename boost::enable_if< boost::mpl::contains<THistory, Event> >::type* = 0)
    {
        if (p_currentState != p_newState)
        {
            TVisitor::execute(p_newState, Detail::CompositeStartVisitor<Pool>(p_pool));
        }
    }

    template<typename Event, typename State, typename Pool>
    static void execute(const State&, const State&, Pool&, typename boost::disable_if< boost::mpl::contains<THistory, Event> >::type* = 0)
    { }
};

} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

