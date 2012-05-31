//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_UNEXPECTEDEVENT_HPP
#define QFSM_BACK_UNEXPECTEDEVENT_HPP

#ifndef QFSM_DEFAULT_UNEXPECTED_EVENT
# define QFSM_DEFAULT_UNEXPECTED_EVENT ::QFsm::Back::UnexpectedEvent
#endif

#include <typeinfo>
#include <stdexcept>

namespace QFsm
{

class UnexpectedEvent : public std::runtime_error
{
public:
    explicit UnexpectedEvent(const char* p_expr)
        : std::runtime_error(p_expr)
    { }
};

namespace Back
{

class UnexpectedEvent
{
public:
    template<typename Event, typename State> void operator()(const Event&)
    {
        throw QFsm::UnexpectedEvent(typeid(Event).name());
    }
};

} // namespace Back
} // namespace QFsm

#endif

