//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_OPERATIONS_SENDINTERNALEVENT_HPP
#define QFSM_FRONT_OPERATIONS_SENDINTERNALEVENT_HPP

#include <boost/type_traits/is_same.hpp>
#include "QFsm/Back/Aux/Extensions.p"
#include "QFsm/Back/Aux/Operation.hpp"
#include "QFsm/Back/Aux/Call.hpp"

namespace QFsm
{
namespace Front
{
namespace Operations
{

QFSM_UML_EXTENSIONS
(
    class SendInternalEvent_ : Back::Aux::Internal { };

    template<typename TInternalEvent, typename TAction, template<typename, typename> class TCall = Back::Aux::Call>
    class SendInternalEvent : public Back::Aux::Operation1<TAction>
    {
    public:
        typedef TAction Action;

        template<typename Event, typename Pool, typename CallBack>
        void operator()(const Event& p_event, Pool& p_pool, const CallBack& p_callBack) const
        {
            p_callBack.sendInternalEvent(TCall<TInternalEvent, TAction>::execute(p_event, p_pool, p_callBack));
        }
    };
)

} // namespace Operations
} // namespace Front
} // namespace QFsm

#endif

