//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_FUSION_DETAIL_COMPOSITEPROXY_HPP
#define QFSM_FRONT_FUSION_DETAIL_COMPOSITEPROXY_HPP

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace QFsm
{
namespace Front
{
namespace Fusion
{
namespace Detail
{

template<typename TIdentifier, typename TFsm>
class CompositeProxy
{
public:
    explicit CompositeProxy(const TFsm& p_fsm)
        : m_fsm(p_fsm)
    { }

    template<typename TEvent> bool processEvent(const TEvent& p_event)
    {
        return m_fsm.processEvent(p_event);
    }

private:
    const TFsm& m_fsm;
};

} // namespace Detail
} // namespace Front
} // namespace Fusion
} // namespace QFsm

#endif

