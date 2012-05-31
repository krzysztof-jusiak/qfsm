//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_EVENTS_HPP
#define QFSM_BACK_AUX_EVENTS_HPP

#include <boost/type_traits/is_base_of.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/set.hpp>
#include "QFsm/Back/Aux/FsmType.hpp"
#include "QFsm/Back/Aux/TransitionTypes.hpp"
#include "QFsm/Front/Operations/None.hpp"

namespace QFsm
{
namespace Back
{
namespace Aux
{

template<typename TDerived>
class Events
{
    template<typename Composite, typename Set = boost::mpl::set0<> >
    struct RegisteredEvents : boost::mpl::fold
        <
            typename Composite::TransitionTable,
            Set,
            boost::mpl::if_
            <
                boost::is_base_of<Back::Aux::FsmType, Back::Aux::InitState<boost::mpl::_2> >,
                RegisteredEvents
                <
                    Back::Aux::InitState<boost::mpl::_2>,
                    boost::mpl::insert<boost::mpl::_1, Back::Aux::Event<boost::mpl::_2> >
                >,
                boost::mpl::if_
                <
                    boost::is_base_of<Back::Aux::FsmType, Back::Aux::TargetState<boost::mpl::_2> >,
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

    struct EventLists : boost::mpl::fold
    <
        typename RegisteredEvents<TDerived>::type,
        boost::mpl::vector0<>,
        boost::mpl::if_
        <
            boost::is_same<boost::mpl::_2, Front::Operations::None>,
            boost::mpl::_1,
            boost::mpl::push_back<boost::mpl::_1, boost::mpl::_2>
        >
    >
    { };

public:
    typedef typename EventLists::type type;
};

} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

