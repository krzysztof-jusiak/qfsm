//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_CONFIG_HPP
#define QFSM_CONFIG_HPP

#include <deque>
#include <boost/shared_ptr.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/config.hpp>

#ifndef QFSM_OPERATION_LIMIT_SIZE
# define QFSM_OPERATION_LIMIT_SIZE 5 //used by Seq, And, Or
#endif

namespace QFsm
{
namespace Back
{
namespace Detail
{
class FsmPolicy_;
class FavorCompilationTime_;
class FavorExecutionSpeed_;
} // namespace Detail
namespace Aux
{
class Logger;
class UnexpectedHandler;
} // namespace Aux
template<typename T> class HeapAllocator;
template<typename T> class StackAllocator;
template<template<typename, typename> class> struct Queue;
template<template<typename> class T = HeapAllocator> struct Allocator;
template<typename = void, typename = void, typename = void, typename = void, typename = void, typename = void> class FavorExecutionSpeed;
template<typename = void, typename = void, typename = void, typename = void, typename = void, typename = void> class FavorCompilationTime;
class CheckOrthogonality;
class DontCheckOrthogonality;
class CacheEnabled;
class CacheDisabled;
class Copyable;
class Noncopyable;
} // namespace Back

namespace Front
{
namespace Aux
{
class SilentLogger;
class SilentUnexpectedHandler;
} // namespace Aux
namespace Operations
{
namespace Detail
{
class History_;
} // namespace Detail
class NoHistory;
class AllEventsHistory;
} // namespace Operations
} // namespace Front
namespace Detail
{
class Generic { };
class Specialized { };
} // namespace Detail

#ifdef NDEBUG
#    if defined(BOOST_HAS_VARIADIC_TMPL) && defined(BOOST_HAS_TEMPLATE_ALIASES)
         template<typename... Args> using QFSM_POLICY = QFsm::Back::FavorCompilationTime<Args...>;
#    else
#        define QFSM_POLICY QFsm::Back::FavorCompilationTime
#    endif
#else
#    if defined(BOOST_HAS_VARIADIC_TMPL) && defined(BOOST_HAS_TEMPLATE_ALIASES)
         template<typename... Args> using QFSM_POLICY = QFsm::Back::FavorDebugSize<Args...>;
#    else
#        define QFSM_POLICY QFsm::Back::FavorDebugSize
#    endif
#endif

/**
 * Example of changing default behavior using specialized class
 *
 * @code
 * #include <QFsm/Config.hpp>
 *
 * namespace QFsm
 * {
 * template<>
 * struct Defaults<QFsm::Back::Aux::Logger, QFsm::Aux::Detail::Specialized>
 * {
 *     typedef MyDefaultLogger type;
 * };
 * } // namespace QFsm
 * @endcode
 */
template<typename T, typename TDefault = Detail::Specialized> struct Defaults;

template<typename TDefault>
struct Defaults<Back::Aux::Logger, TDefault>
{
    typedef QFsm::Front::Aux::SilentLogger type;
};

template<typename TDefault>
struct Defaults<Back::Aux::UnexpectedHandler, TDefault>
{
    typedef QFsm::Front::Aux::SilentUnexpectedHandler type;
};

template<typename TDefault>
struct Defaults<Back::Detail::FsmPolicy_, TDefault>
{
    typedef QFSM_POLICY<> type;
};

template<typename TDefault>
struct Defaults<Front::Operations::Detail::History_, TDefault>
{
    typedef Front::Operations::NoHistory type;
};

template<typename TDefault>
struct Defaults<Back::Detail::FavorExecutionSpeed_, TDefault>
{
    typedef Back::DontCheckOrthogonality Orthogonality;
    typedef Back::CacheEnabled Cache;
    typedef Back::Copyable Copy;
    typedef Back::Queue<boost::circular_buffer> Queue;
    typedef Back::Allocator<Back::HeapAllocator> Allocator;
};

template<typename TDefault>
struct Defaults<Back::Detail::FavorCompilationTime_, TDefault>
{
    typedef Back::DontCheckOrthogonality Orthogonality;
    typedef Back::CacheDisabled Cache;
    typedef Back::Copyable Copy;
    typedef Back::Queue<std::deque> Queue;
    typedef Back::Allocator<Back::HeapAllocator> Allocator;
};

} // namespace QFsm

#endif

