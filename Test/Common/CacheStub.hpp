//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_TEST_COMMON_CACHESTUB_HPP
#define QFSM_TEST_COMMON_CACHESTUB_HPP

#include <boost/optional.hpp>

namespace QFsm
{
namespace Test
{
namespace Common
{

class CacheStub
{
public:
    void reset() { }
    template<typename T> void set(bool) { }
    template<typename T> boost::optional<bool> get() const { return boost::optional<bool>(); }
};

} // namespace Common
} // namespace Test
} // namespace QFsm

#endif

