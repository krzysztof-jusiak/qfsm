//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_POLICY_HPP
#define QFSM_BACK_POLICY_HPP

#ifndef QFSM_FSM_DEFAULT_POLICY
# ifdef NDEBUG
#  define QFSM_FSM_DEFAULT_POLICY ::QFsm::Back::FavorExecutionSpeed
# else
#  define QFSM_FSM_DEFAULT_POLICY ::QFsm::Back::FavorCompilationTime
# endif
#endif

namespace QFsm
{
namespace Back
{

struct FavorCompilationTime { };
struct FavorExecutionSpeed { };

} // namespace Back
} // namespace QFsm

#endif

