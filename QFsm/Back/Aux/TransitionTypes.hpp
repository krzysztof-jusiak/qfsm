//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_TRANSITIONTYPES_HPP
#define QFSM_BACK_AUX_TRANSITIONTYPES_HPP

namespace QFsm
{
namespace Back
{
namespace Aux
{

template<typename Transition> struct InitState
{
    typedef typename Transition::StateInit type;
};

template<typename Transition> struct TargetState
{
    typedef typename Transition::StateTarget type;
};

template<typename Transition> struct Event
{
    typedef typename Transition::Event type;
};

template<typename Transaction> struct Action
{
    typedef typename Transaction::Action type;
};

template<typename Transaction> struct Guard
{
    typedef typename Transaction::Guard type;
};

} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

