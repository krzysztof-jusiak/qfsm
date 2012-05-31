//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_UTILITY_STATE_HPP
#define QFSM_UTILITY_STATE_HPP

namespace QFsm
{
namespace Utility
{

/**
 * @code
 * class Fsm : public QFsm::Front::Fsm
 * {
 *     enum { S1, S2, S3 };
 *
 *     typedef boost::mpl::vector
 *     <
 *         Transition < State<S1> , e1 , State<S2> >,
 *         Transition < State<S2> , e2 , State<S3> >
 *     >
 *     TransitionTable;
 * };
 * @endcode
 *
 * @tparam int state
 */
template<int> struct State { };

} // namespace Utility
} // namespace QFsm

#endif

