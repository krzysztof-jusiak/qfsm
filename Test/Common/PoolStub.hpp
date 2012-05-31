//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_TEST_COMMON_POOLSTUB_HPP
#define QFSM_TEST_COMMON_POOLSTUB_HPP

#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include "QFsm/Front/Operations/None.hpp"
#include <cassert>

namespace QFsm
{
namespace Test
{
namespace Common
{

namespace Detail
{

template<typename TMember, int> class Acquire
{
public:
    template<typename T> T& acquire(typename boost::enable_if< boost::is_same<T, TMember> >::type* = 0)
    {
        return member;
    }

private:
    TMember member;
};

template<int Value> class Acquire<Front::Operations::None, Value>
{
public:
    int acquire;
};

} // namespace

template<typename TComposite, typename TAction, typename TGuard>
class PoolStub : public Detail::Acquire<TComposite, 0>,
                 public Detail::Acquire<TAction, 1>,
                 public Detail::Acquire<TGuard, 2>
{
public:
    using Detail::Acquire<TComposite, 0>::acquire;
    using Detail::Acquire<TAction, 1>::acquire;
    using Detail::Acquire<TGuard, 2>::acquire;
};

} // namespace Common
} // namespace Test
} // namespace QFsm

#endif

