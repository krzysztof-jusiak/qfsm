//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_BASE_DETAIL_KEYS_HPP
#define QFSM_FRONT_BASE_DETAIL_KEYS_HPP

#include <boost/mpl/set.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include "QFsm/Front/Operations/None.hpp"
#include "QFsm/Back/Aux/Detail/Flatten.hpp"
#include "QFsm/Back/Aux/Operation.hpp"
#include "QFsm/Back/Aux/FsmType.hpp"
#include "QFsm/Back/Aux/TransitionTypes.hpp"

namespace QFsm
{
namespace Front
{
namespace Detail
{

template<typename TransitionTable, typename UnexpectedEvent, typename Logger>
struct Keys : boost::mpl::fold
    <
        typename boost::mpl::fold
        <
            typename Back::Aux::Detail::Flatten
            <
                boost::mpl::vector4
                <
                    typename boost::mpl::fold
                    <
                        TransitionTable,
                        boost::mpl::set0<>,
                        boost::mpl::if_
                        <
                            boost::is_base_of<Back::Aux::FsmType, Back::Aux::InitState<boost::mpl::_2> >,
                            boost::mpl::insert<boost::mpl::_1, Back::Aux::InitState<boost::mpl::_2> >,
                            boost::mpl::_1
                        >
                    >::type,
                    typename boost::mpl::fold
                    <
                        TransitionTable,
                        boost::mpl::set0<>,
                        boost::mpl::if_
                        <
                            boost::is_base_of<Back::Aux::FsmType, Back::Aux::TargetState<boost::mpl::_2> >,
                            boost::mpl::insert<boost::mpl::_1, Back::Aux::TargetState<boost::mpl::_2> >,
                            boost::mpl::_1
                        >
                    >::type,
                    typename boost::mpl::fold
                    <
                        TransitionTable,
                        boost::mpl::vector0<>,
                        boost::mpl::if_
                        <
                            boost::is_base_of<Back::Aux::Operation, Back::Aux::Guard<boost::mpl::_2> >,
                            Back::Aux::Detail::Flatten< Back::Aux::Guard<boost::mpl::_2> >,
                            boost::mpl::push_back<boost::mpl::_1, Back::Aux::Guard<boost::mpl::_2> >
                        >
                    >::type,
                    typename boost::mpl::fold
                    <
                        TransitionTable,
                        boost::mpl::vector0<>,
                        boost::mpl::if_
                        <
                            boost::is_base_of<Back::Aux::Operation, Back::Aux::Action<boost::mpl::_2> >,
                            Back::Aux::Detail::Flatten< Back::Aux::Action<boost::mpl::_2> >,
                            boost::mpl::push_back<boost::mpl::_1, Back::Aux::Action<boost::mpl::_2> >
                        >
                    >::type
                >
            >::type,
            boost::mpl::set0<>,
            boost::mpl::insert<boost::mpl::_1, boost::mpl::_2>
        >::type,
        boost::mpl::vector2<UnexpectedEvent, Logger>,
        boost::mpl::if_
        <
            boost::is_same<boost::mpl::_2, Front::Operations::None>,
            boost::mpl::_1,
            boost::mpl::push_back<boost::mpl::_1, boost::mpl::_2>
        >
    >
{ };

} // namespace Detail
} // namespace Front
} // namespace QFsm

#endif

