//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_CUNEXPECTEDHANDLER_HPP
#define QFSM_FRONT_CUNEXPECTEDHANDLER_HPP

#include <exception>
#include "QFsm/Back/Aux/Concept.hpp"
#include "QFsm/Back/Aux/UnexpectedHandler.hpp"

namespace QFsm
{
namespace Front
{

/**
 * Unexpected handler concept
 *
 * @code
 * class MyUnexpectedHandler : public QFsm::Front::CUnexpectedHandler<MyUnexpectedHandler>
 * {
 * public:
 *      template<typename T> void operator()(const std::exception& p_exception) { }
 *      template<typename Event, typename State> void operator()(const Event&) { }
 * };
 * @endcode
 */
template<typename T>
class CUnexpectedHandler : public QFsm::Aux::Concept<T>, QFsm::Back::Aux::UnexpectedHandler
{
public:
    void conceptUsage()
    {
        //template<typename T> void operator()(const std::exception& p_exception);
        static_cast<T*>(this)->template operator()<QFsm::Aux::AnyType<0> >(std::exception());

        //template<typename Event, typename State> void operator()(const Event&);
        static_cast<T*>(this)->template operator()<QFsm::Aux::AnyType<1>, QFsm::Aux::AnyType<2> >(QFsm::Aux::AnyType<1>());
    }
};

} // namespace Front
} // namespace QFsm

#endif

