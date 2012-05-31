//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_COMPILATION_STATE_HPP
#define QFSM_BACK_DETAIL_COMPILATION_STATE_HPP

#include <boost/type_traits/is_base_of.hpp>
#include <boost/mpl/int.hpp>
#include "QFsm/Back/Aux/FsmType.hpp"
#include "QFsm/Back/Aux/State.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{
namespace Compilation
{

struct State
{
    explicit State(int p_id = 0)
        : id(p_id)
    { }

    int id;
};

} // namespace Compilation
} // namespace Detail

namespace Aux
{
template<typename TFsm>
class State<Back::Detail::Compilation::State, TFsm>
{
public:
    static void init(Back::Detail::Compilation::State& p_state, const boost::mpl::int_<0>&)
    {
        p_state = Back::Detail::Compilation::State(boost::mpl::find<typename TFsm::States, typename TFsm::InitialState>::type::pos::value);
    }

    template<int region> static void init(Back::Detail::Compilation::State& p_state, const boost::mpl::int_<region>&)
    {
        typedef typename boost::mpl::at_c<typename TFsm::InitialState, region - 1>::type state;
        p_state = Back::Detail::Compilation::State(boost::mpl::find<typename TFsm::States, state>::type::pos::value);
    }

    template<typename TState> static bool equals(const Back::Detail::Compilation::State& p_state)
    {
        return static_cast<int>(boost::mpl::find<typename TFsm::States, TState>::type::pos::value) == p_state.id;
    }
};
} // namespace Aux

} // namespace Back
} // namespace QFsm

#endif

