//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_FSMFAVOR_HPP
#define QFSM_BACK_FSMFAVOR_HPP

#include <boost/mpl/if.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/type_traits/is_same.hpp>
#include "QFsm/Back/Policy.hpp"
#include "QFsm/Back/Aux/TransitionTypes.hpp"
#include "QFsm/Back/Aux/Detail/Ctor.hpp"
#include "QFsm/Back/FsmInternal.hpp"
#include "QFsm/Back/Detail/Execution/Fsm.hpp"
#include "QFsm/Back/Detail/Compilation/Fsm.hpp"

namespace QFsm
{
namespace Back
{

namespace Detail
{

template<typename TDerived, typename State>
struct Helper : public TDerived
{
    typedef State InitialState;
};

template<typename TDerived>
struct Derived : boost::mpl::if_
<
    boost::is_same<typename TDerived::InitialState, boost::mpl::_1>,
    Detail::Helper
    <
         TDerived,
         typename Aux::InitState<typename boost::mpl::begin<typename TDerived::TransitionTable>::type::type>::type
    >,
    TDerived
>
{ };

} // namespace Detail

template
<
    typename TDerived,
    typename TPool,
    typename Policy
>
class FsmFavor;

template
<
    typename TDerived,
    typename TPool
>
class FsmFavor<TDerived, TPool, FavorExecutionSpeed>
    : public FsmInternal< Detail::Execution::Fsm<typename Detail::Derived<TDerived>::type, TPool> >
{
    typedef FsmInternal< Detail::Execution::Fsm<typename Detail::Derived<TDerived>::type, TPool> > Base;

public:
    CTOR_REF(FsmFavor, Base, { })
};

template
<
    typename TDerived,
    typename TPool
>
class FsmFavor<TDerived, TPool, FavorCompilationTime>
    : public FsmInternal< Detail::Compilation::Fsm<typename Detail::Derived<TDerived>::type, TPool> >
{
    typedef FsmInternal< Detail::Compilation::Fsm<typename Detail::Derived<TDerived>::type, TPool> > Base;

public:
    CTOR_REF(FsmFavor, Base, { })
};

} // namespace Back
} // namespace QFsm

#endif

