//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_PARAMETERS_HPP
#define QFSM_BACK_AUX_PARAMETERS_HPP

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/deref.hpp>
#include "QFsm/Back/Aux/Parameter.hpp"
#include "QFsm/Back/Aux/Composite.hpp"
#include "QFsm/Back/FsmPolicy.hpp"
#include "QFsm/Front/Aux/SilentLogger.hpp"
#include "QFsm/Front/Aux/SilentUnexpectedHandler.hpp"
#include "QFsm/Front/Operations/Transition.hpp"
#include "QFsm/Front/Operations/History.hpp"
#include "QFsm/Config.hpp"

namespace QFsm
{
namespace Back
{
namespace Aux
{

template<typename TParameters, typename TDefault, typename TLambda>
struct Parameter : boost::mpl::fold
    <
        TParameters,
        TDefault,
        boost::mpl::if_
        <
            TLambda,
            boost::mpl::_2,
            boost::mpl::_1
        >
    >
{ };

template<typename TParameters, typename T, typename TBase>
struct Parameter : Parameter
    <
        TParameters,
        QFsm::Defaults<T>::p_type, boost::is_base_of<TBase, boost::mpl::_2>
    >::type
{ };

template<typename TSeq> struct PDerived : Parameter
    <
        TSeq,
        void,
        boost::is_base_of<Composite, boost::mpl::_2>
    >
{ };

template<typename TSeq> struct PTransitionTable : Parameter
    <
        TSeq,
        void,
        boost::mpl::and_
        <
            boost::mpl::is_sequence<boost::mpl::_2>,
            boost::is_base_of<Front::Operations::Detail::Transition_, boost::mpl::deref<boost::mpl::begin<boost::mpl::_2> > >
        >
    >
{ };

template<typename TSeq> struct PInitialState : Parameter
    <
        TSeq,
        boost::mpl::_1,
        boost::mpl::and_
        <
            boost::mpl::and_
            <
                boost::mpl::not_< boost::is_same<void, boost::mpl::_2> >,
                boost::mpl::not_< boost::is_base_of<Back::Aux::UnexpectedHandler, boost::mpl::_2> >
            >,
            boost::mpl::and_
            <
                boost::mpl::not_< boost::is_base_of<Back::Detail::FsmPolicy_, boost::mpl::_2> >,
                boost::mpl::not_< boost::is_base_of<Back::Aux::Logger, boost::mpl::_2> >
            >
        >
    >
{ };

template<typename TSeq> struct PHistory : Parameter
    <
        TSeq,
        QFsm::Defaults<Front::Operations::Detail::History_>::type,
        boost::is_base_of<Front::Operations::Detail::History_, boost::mpl::_2>
    >
{ };

template<typename TSeq> struct PLogger : Parameter
    <
        TSeq,
        QFsm::Defaults<Back::Aux::Logger>::type,
        boost::is_base_of<Back::Aux::Logger, boost::mpl::_2>
    >
{ };

template<typename TSeq> struct PUnexepctedHandler : Parameter
    <
        TSeq,
        QFsm::Defaults<Back::Aux::UnexpectedHandler>::type,
        boost::is_base_of<Back::Aux::UnexpectedHandler, boost::mpl::_2>
    >
{ };

template<typename TSeq> struct PPolicy : Parameter
    <
        TSeq,
        QFsm::Defaults<Back::Detail::FsmPolicy_>::type,
        boost::is_base_of<Back::Detail::FsmPolicy_, boost::mpl::_2>
    >
{ };

} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

