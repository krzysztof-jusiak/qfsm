//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_COMPLETIONTRANSITION_HPP
#define QFSM_BACK_DETAIL_COMPLETIONTRANSITION_HPP

#include <boost/utility/enable_if.hpp>
#include "QFsm/Back/Aux/TransitionTypes.hpp"
#include "QFsm/Back/Aux/Contains.hpp"
#include "QFsm/Front/Operations/None.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{

template<typename TFsmBase, typename Enable = void> class CompletionTransition
{
public:
    static void execute(TFsmBase&, bool = true) { }
};

template<typename TFsmBase>
class CompletionTransition< TFsmBase, typename boost::enable_if< Aux::Contains<typename TFsmBase::Derived, Aux::Event, Front::Operations::None> >::type>
{
public:
    static void execute(TFsmBase& p_fsm, bool p_handled = true)
    {
        if (p_handled)
        {
            p_fsm.processEventImpl(Front::Operations::None());
        }
    }
};

} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

