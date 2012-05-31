//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <gtest/gtest.h>
#include "QFsm/Back/Logger.hpp"
#include "Common/States.hpp"
#include "Common/Guards.hpp"
#include "Common/Actions.hpp"
#include "Common/Events.hpp"

namespace QFsm
{

using namespace Test::Common;

namespace Back
{
namespace UT
{

class LoggerStub
{
public:
    void onEntryAction(const std::type_info& )
    {

    }

    void onExitAction(const std::type_info&)
    {
    };

    void onEventReceived(const std::type_info&)
    {
    }

    void onUnexpectedEventReceived(const std::type_info&)
    {
    }

    void onStateTransition(const std::type_info&, const std::type_info&)
    {
    }

    void onGuardExecuted(const std::type_info&)
    {
    }

    void onActionExecuted(const std::type_info&)
    {
    }
};

class PoolStub
{
public:
    template<typename T> T& get() { return m_logger; }

private:
    LoggerStub m_logger;
};

struct EmptyPoolStub { };

TEST(LoggerTest, Disabled)
{
    //given
    typedef Logger<LoggerDisabled> Logger;
    //EmptyPoolStub l_pool;

    //when & then
    //Logger::onEntryAction<State1>(l_pool);
    //Logger::onEntryAction(l_pool, typeid(State1));
    //Logger::onExitAction<State1>(l_pool);
    //Logger::onExitAction(l_pool, typeid(State1));
    //Logger::onEventReceived<State1>(l_pool);
    //Logger::onUnexpectedEventReceived<State1>(l_pool);
    //Logger::onStateTransition<State1, State2>(l_pool);
    //Logger::onStateTransition(l_pool, typeid(State1), typeid(State2));
    //Logger::onGuardExecuted< Guard<> >(l_pool);
    //Logger::onActionExecuted< Action >(l_pool);
    //Logger::onEvent<e1, State1>(l_pool);
}

TEST(LoggerTest, Enabled)
{
    //given
    typedef Logger<LoggerStub> Logger;
    PoolStub l_pool;

    //when
    Logger::onEntryAction<State1>(l_pool);
}

} // namespace UT
} // namespace Back
} // namespace QFsm

