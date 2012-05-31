//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_TEST_COMMON_ACTIONS_HPP
#define QFSM_TEST_COMMON_ACTIONS_HPP

namespace QFsm
{
namespace Test
{
namespace Common
{

template<int = 0> class Action
{
public:
    template<typename Event> void operator()(const Event&)
    {
        calls()++;
    }

    static int& calls()
    {
        static int s_calls = 0;
        return s_calls;
    }
};

} // namespace Common
} // namespace Test
} // namespace QFsm

#endif

