//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_TEST_COMMON_DEFERRALEVENTSTB_HPP
#define QFSM_TEST_COMMON_DEFERRALEVENTSTB_HPP

#include <vector>
#include <boost/function.hpp>

namespace QFsm
{
namespace Test
{
namespace Common
{

class DeferralEventStub
{
    typedef boost::function<void()> ExecuteEvent;

public:
    void init() { }
    void execute(bool) { }

    void addDeferralEvent(const ExecuteEvent& p_event)
    {
        addDeferralEventCalls.push_back(p_event);
    }

    std::vector<ExecuteEvent> addDeferralEventCalls;
};

} // namespace Common
} // namespace Test
} // namespace QFsm

#endif

