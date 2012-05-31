//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_EXECUTION_STATE_HPP
#define QFSM_BACK_DETAIL_EXECUTION_STATE_HPP

#include <boost/mpl/at.hpp>
#include <boost/mpl/find.hpp>
#include "QFsm/Back/Aux/State.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{
namespace Execution
{

typedef int State;

} // namespace Execution
} // namespace Detail

namespace Aux
{
template<typename TFsm>
class State<Back::Detail::Execution::State, TFsm>
{
public:
    static void init(Back::Detail::Execution::State& p_state, const boost::mpl::int_<0>&)
    {
        p_state = boost::mpl::find<typename TFsm::States, typename TFsm::InitialState>::type::pos::value;
    }

    template<int region> static void init(Back::Detail::Execution::State& p_state, const boost::mpl::int_<region>&)
    {
        typedef typename boost::mpl::at_c<typename TFsm::InitialState, region - 1>::type state;
        p_state = boost::mpl::find<typename TFsm::States, state>::type::pos::value;
    }

    template<typename TState> static bool equals(const Back::Detail::Execution::State& p_state)
    {
        return static_cast<int>(boost::mpl::find<typename TFsm::States, TState>::type::pos::value) == p_state;
    }
};
} // namespace Aux

} // namespace Back
} // namespace QFsm

#endif

