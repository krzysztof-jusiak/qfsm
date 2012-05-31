//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_FUSION_DETAIL_ACTIONPROXY_HPP
#define QFSM_FRONT_FUSION_DETAIL_ACTIONPROXY_HPP

#include <boost/shared_ptr.hpp>
#include "QFsm/Front/IAction.hpp"

namespace QFsm
{
namespace Front
{
namespace Fusion
{
namespace Detail
{

template<typename TIdentifier, typename TEvent>
class ActionProxy
{
public:
    explicit ActionProxy(const boost::shared_ptr< Front::Detail::IAction<TEvent> >& p_action)
        : m_action(p_action)
    { }

    void operator()(const TEvent& p_event)
    {
        (*m_action)(p_event);
    }

    template<typename Event> void operator()(const Event&) { }

private:
    boost::shared_ptr< Front::Detail::IAction<TEvent> > m_action;
};

} // namespace Detail
} // namespace Front
} // namespace Fusion
} // namespace QFsm

#endif

