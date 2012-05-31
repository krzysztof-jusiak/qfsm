//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_FSM_HPP
#define QFSM_FRONT_FSM_HPP

#include <boost/mpl/vector.hpp>
#include <boost/mpl/placeholders.hpp>
#include "QFsm/Back/Logger.hpp"
#include "QFsm/Back/UnexpectedEvent.hpp"
#include "QFsm/Front/Operations/None.hpp"

namespace QFsm
{

class Fsm
{
public:
    typedef boost::mpl::_1 InitialState; ///< first state from transition table will be taken
    typedef boost::mpl::vector0<> TransitionTable;
    typedef QFSM_DEFAULT_UNEXPECTED_EVENT UnexpectedEvent;
    typedef QFSM_DEFAULT_LOGGER Logger;
};

} // namespace QFsm

#endif

