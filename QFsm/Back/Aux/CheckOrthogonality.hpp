//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_CHECKORTHOGONALITY_HPP
#define QFSM_BACK_AUX_CHECKORTHOGONALITY_HPP

#include <boost/mpl/fold.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/is_sequence.hpp>
#include "QFsm/Back/Aux/Flatten.hpp"
#include "QFsm/Back/Aux/TransitionTypes.hpp"

namespace QFsm
{
namespace Back
{
namespace Aux
{

/**
 * One state should belongs only to the one orthogonal region
 * BOOST_MPL_ASSERT((QFsm::Back::Aux::CheckOrthogonality<TInitialState, TTransitionTable>));
 */
template<typename TOrthogonality, typename TInitialState, typename TTransitionTable, bool assert = true>
class CheckOrthogonality
{
    BOOST_MPL_ASSERT((boost::mpl::is_sequence<TTransitionTable>));

    template<typename State, typename Set = boost::mpl::set0<> >
    struct GetRecursivelyTargetStates : boost::mpl::fold
        <
            TTransitionTable,
            Set,
            boost::mpl::if_
            <
                boost::is_same<Back::Aux::InitState<boost::mpl::_2>, State>,
                boost::mpl::if_
                <
                    boost::mpl::has_key<boost::mpl::_1, Back::Aux::TargetState<boost::mpl::_2> >,
                    boost::mpl::_1,
                    GetRecursivelyTargetStates
                    <
                        Back::Aux::TargetState<boost::mpl::_2>,
                        boost::mpl::insert<boost::mpl::_1, Back::Aux::TargetState<boost::mpl::_2> >
                    >
                >,
                boost::mpl::_1
            >
        >
    { };

    struct JoinAllRegionsStates : QFsm::Aux::Flatten
        <
            boost::mpl::fold
            <
                TInitialState,
                boost::mpl::vector0<>,
                boost::mpl::push_back<boost::mpl::_1, GetRecursivelyTargetStates<boost::mpl::_2> >
            >
        >
    { };

    typedef typename QFsm::Aux::Flatten
    <
        typename boost::mpl::fold
        <
            TInitialState,
            boost::mpl::vector0<>,
            boost::mpl::push_back<boost::mpl::_1, GetRecursivelyTargetStates<boost::mpl::_2> >
        >::type
    >::type RegionsStatesJoined;

    struct NotTrulyOrthogonalStates : boost::mpl::fold
        <
            RegionsStatesJoined,
            boost::mpl::set0<>,
            boost::mpl::if_
            <
                boost::mpl::greater< boost::mpl::count<RegionsStatesJoined, boost::mpl::_2>, boost::mpl::size_t<1> >,
                boost::mpl::insert<boost::mpl::_1, boost::mpl::_2>,
                boost::mpl::_1
            >
        >
    { };

public:
    typedef typename boost::mpl::empty<typename NotTrulyOrthogonalStates::type> type;

    //regions are truly orthogonal if each state belongs exactly to one orthogonal region
    //states which belongs to more than one orthogonal regions are listed by type
    BOOST_MPL_ASSERT_MSG((boost::mpl::or_<type, boost::mpl::bool_<!assert> >::value), REGIONS_ARE_NOT_TRULY_ORTHOGONAL, (typename NotTrulyOrthogonalStates::type));
};

template<typename TInitialState, typename TTransitionTable, bool assert>
class CheckOrthogonality<DontCheckOrthogonality, TInitialState, TTransitionTable, assert> : public boost::mpl::true_ { };

} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

