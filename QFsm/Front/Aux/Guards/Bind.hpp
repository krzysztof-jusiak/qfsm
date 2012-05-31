//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_OPERATIONS_BIND_HPP
#define QFSM_FRONT_OPERATIONS_BIND_HPP

#include <boost/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/is_same.hpp>
#include "QFsm/Back/Aux/Operation.hpp"


namespace QFsm
{
namespace Front
{
namespace Operations
{

namespace Detail
{

template<typename T, T, typename, typename> class AcquireDynamic;

template<typename T, T Func, typename Base>
class AcquireDynamic<T, Func, void, Base>
{
public:
    template<typename Event, typename Pool, typename CallBack>
    void operator()(const Event& p_event, Pool& p_pool, const CallBack&) const
    {
        (p_pool.template acquire<Base>().*Func)(p_event);
    }
};

template<typename T, T Func, typename Base>
class AcquireDynamic<T, Func, bool, Base>
{
public:
    template<typename Event, typename Pool, typename CallBack>
    void operator()(const Event& p_event, Pool& p_pool, const CallBack&) const
    {
        return (p_pool.template acquire<Base>().*Func)(p_event);
    }
};

template<typename T, T, typename> class AcquireStatic;

template<typename T, T Func>
class AcquireStatic<T, Func, void>
{
public:
    template<typename Event, typename Pool, typename CallBack>
    void operator()(const Event& p_event, Pool&, const CallBack&) const
    {
        Func(p_event);
    }
};

template<typename T, T Func>
class AcquireStatic<T, Func, bool>
{
public:
    template<typename Event, typename Pool, typename CallBack>
    bool operator()(const Event& p_event, Pool&, const CallBack&) const
    {
        return Func(p_event);
    }
};

} // namespace Detail



} // namespace Operations
} // namespace Front
} // namespace QFsm

#endif

