//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_STATES_HPP
#define QFSM_BACK_AUX_STATES_HPP

#include <boost/mpl/set.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/push_back.hpp>
#include "QFsm/Back/Aux/TransitionTypes.hpp"

namespace QFsm
{
namespace Back
{
namespace Aux
{

template<typename TransitionTable>
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
    >
{ };

} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

