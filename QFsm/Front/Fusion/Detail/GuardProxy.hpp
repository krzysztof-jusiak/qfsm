//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_FUSION_DETAIL_GUARDPROXY_HPP
#define QFSM_FRONT_FUSION_DETAIL_GUARDPROXY_HPP

#include <boost/shared_ptr.hpp>
#include "QFsm/Front/IGuard.hpp"

namespace QFsm
{
namespace Front
{
namespace Fusion
{
namespace Detail
{

template<typename TIdentifier, typename TEvent>
class GuardProxy
{
public:
    explicit GuardProxy(const boost::shared_ptr< Front::Detail::IGuard<TEvent> >& p_guard)
        : m_guard(p_guard)
    { }

    bool operator()(const TEvent& p_event)
    {
        return (*m_guard)(p_event);
    }

    template<typename Event> bool operator()(const Event&) { return true; }

private:
    boost::shared_ptr< Front::Detail::IGuard<TEvent> > m_guard;
};

} // namespace Detail
} // namespace Front
} // namespace Fusion
} // namespace QFsm

#endif

