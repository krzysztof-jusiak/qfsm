//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_WRAPPER_HPP
#define QFSM_BACK_AUX_WRAPPER_HPP

#include <boost/mpl/set.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/set.hpp>
#include "QFsm/Back/Aux/Composite.hpp"
#include "QFsm/Back/Aux/TransitionTypes.hpp"
#include "QFsm/Front/Operations/None.hpp"

namespace QFsm
{
namespace Back
{
namespace Aux
{

template
<
    typename TTransitionTable,
    typename TInitialState,
    typename THistory,
    typename TPool,
    typename TPolicy
>
class Wrapper
{
    BOOST_MPL_ASSERT((boost::mpl::is_sequence<TTransitionTable>));

    template<typename T, typename TSet = boost::mpl::set0<> >
    struct RegisteredEvents : boost::mpl::fold
        <
            T,
            TSet,
            boost::mpl::if_
            <
                boost::is_base_of<Back::Aux::Composite, Back::Aux::InitState<boost::mpl::_2> >,
                RegisteredEvents
                <
                    Back::Aux::InitState<boost::mpl::_2>,
                    boost::mpl::insert<boost::mpl::_1, Back::Aux::Event<boost::mpl::_2> >
                >,
                boost::mpl::if_
                <
                    boost::is_base_of<Back::Aux::Composite, Back::Aux::TargetState<boost::mpl::_2> >,
                    RegisteredEvents
                    <
                        Back::Aux::TargetState<boost::mpl::_2>,
                        boost::mpl::insert<boost::mpl::_1, Back::Aux::Event<boost::mpl::_2> >
                    >,
                    boost::mpl::insert<boost::mpl::_1, Back::Aux::Event<boost::mpl::_2> >
                >
            >
        >
    { };

public:
    typedef TTransitionTable TransitionTable;

    struct InitialState : boost::mpl::if_
        <
            boost::is_same<TInitialState, boost::mpl::_1>,
            typename Aux::InitState<typename boost::mpl::deref<typename boost::mpl::begin<TransitionTable>::type>::type>::type,
            TInitialState
        >::type
    { };

    typedef THistory History;
    typedef TPool Pool;
    typedef TPolicy Policy;

    struct States : boost::mpl::fold
        <
            typename boost::mpl::fold
            <
                TransitionTable,
                boost::mpl::set0<>,
                boost::mpl::insert
                <
                    boost::mpl::insert
                    <
                        boost::mpl::_1,
                        TargetState<boost::mpl::_2>
                    >,
                    InitState<boost::mpl::_2>
                >
            >::type,
            boost::mpl::vector0<>,
            boost::mpl::push_back
            <
                boost::mpl::_1, boost::mpl::_2
            >
        >::type
    { };

    struct Events : boost::mpl::fold
        <
            typename RegisteredEvents<TransitionTable>::type,
            boost::mpl::vector0<>,
            boost::mpl::if_
            <
                boost::is_same<boost::mpl::_2, Front::Operations::None>,
                boost::mpl::_1,
                boost::mpl::push_back<boost::mpl::_1, boost::mpl::_2>
            >
        >::type
    { };
};

} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

