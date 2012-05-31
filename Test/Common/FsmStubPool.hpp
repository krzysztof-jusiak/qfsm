//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_TEST_COMMON_FSMSTUBPOOL_HPP
#define QFSM_TEST_COMMON_FSMSTUBPOOL_HPP

#include <gtest/gtest.h>
#include <typeinfo>
#include <vector>
#include "QFsm/Front/Operations/None.hpp"
#include "Common/PoolStub.hpp"
#include "Common/CacheStub.hpp"
#include "QFsm/Back/Logger.hpp"

namespace QFsm
{
namespace Test
{
namespace Common
{

template<typename T0 = Front::Operations::None, typename T1 = Front::Operations::None, typename T2 = Front::Operations::None>
class FsmStubPool
{
public:
    typedef Back::Logger<Back::LoggerDisabled> Log;
    typedef PoolStub<T0, T1, T2> Pool;

    struct Policy
    {
        typedef void Orthogonality;
        typedef void Cache;
    };

    Pool pool;
    CacheStub cache;
};

} // namespace Common
} // namespace Test
} // namespace QFsm

#endif

