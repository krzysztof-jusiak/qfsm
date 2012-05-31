//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_FSMBASE_HPP
#define QFSM_BACK_FSMBASE_HPP

#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/assert.hpp>
#include "QFsm/Back/Aux/Detail/Ctor.hpp"
#include "QFsm/Back/Aux/Detail/Trace.hpp"
#include "QFsm/Back/Aux/Internal.hpp"
#include "QFsm/Back/Aux/States.hpp"
#include "QFsm/Back/Aux/Events.hpp"
#include "QFsm/Back/Aux/FsmType.hpp"
#include "QFsm/Back/Logger.hpp"

#include "QFsm/Back/Detail/Init.hpp"
#include "QFsm/Back/Detail/HandleEvent.hpp"
#include "QFsm/Back/Detail/Transition.hpp"
#include "QFsm/Back/Detail/UnexpectedEvent.hpp"
#include "QFsm/Back/Detail/Visitor.hpp"

#if defined(QFSM_EXTENSIONS_UML)
# include "QFsm/Back/Detail/OnAction.hpp"
# include "QFsm/Back/Detail/CompletionTransition.hpp"
# include "QFsm/Back/Detail/Composite.hpp"
# include "QFsm/Back/Detail/DeferralEvent.hpp"
# include "QFsm/Back/Detail/InternalEvent.hpp"
# include "QFsm/Back/Detail/Terminate.hpp"
#endif

#if defined(QFSM_EXTENSIONS_NON_UML)
# include "QFsm/Back/Detail/Interrupt.hpp"
# include "QFsm/Back/Detail/Else.hpp"
#endif

namespace QFsm
{
namespace Back
{

template
<
    typename TFsm,
    typename TDerived,
    typename TPool,
    typename TState
>
class FsmBase : Back::Aux::FsmType, public TDerived
{
public:
    typedef TFsm Fsm;
    typedef TDerived Derived;
    typedef TState State;
    typedef typename boost::remove_reference<TPool>::type Pool;
    typedef Logger<typename TDerived::Logger> Log;

    typedef typename Aux::States<typename TDerived::TransitionTable>::type States;
    typedef typename Aux::Events<TDerived>::type Events;

    CTOR_REF(FsmBase, pool,
        {
            TRACE("transition table: %s", Aux::Detail::printType<typename TDerived::TransitionTable>().c_str());
            TRACE("initial state: %s", Aux::Detail::printType<typename TDerived::InitialState>().c_str());
            Detail::Init<FsmBase>::execute(*this);
        }
    )

    void start()
    {
       QFSM_UML_EXTENSIONS(
            Detail::OnAction<FsmBase, Front::Operations::OnEntry>::execute(*this);
            Detail::CompletionTransition<FsmBase>::execute(*this);
        )
    }

    void stop()
    {
        QFSM_UML_EXTENSIONS(
            Detail::OnAction<FsmBase, Front::Operations::OnExit>::execute(*this);
        )
    }

    template<typename Event> bool processEvent(const Event& p_event)
    {
        TRACE("[%s]", typeid(Event).name());

        BOOST_MPL_ASSERT_MSG(
            (!boost::is_base_of<Aux::Internal, Event>::value),
            INTERNAL_TYPES_ARE_NOT_ALLOWED,
            (Event)
        );

        Log::template onEventReceived<Event>(pool);

        return processEventImpl(p_event);
    }

    template<typename Visitor> void visitCurrentStates(Visitor p_visitor)
    {
        Detail::Visitor<FsmBase>::execute(*this, p_visitor);
    }

#   define BOOST_PP_LOCAL_LIMITS (1, BOOST_MPL_LIMIT_VECTOR_SIZE)
#   define FSMBASE_SET_IMPL(z, n, text) text.set<T##n>(p_arg##n);

#   define BOOST_PP_LOCAL_MACRO(n)\
        template<BOOST_PP_ENUM_PARAMS(n, typename T)> void set(BOOST_PP_ENUM_BINARY_PARAMS(n, T, p_arg))\
        {\
            BOOST_PP_REPEAT(n, FSMBASE_SET_IMPL, pool)\
        }

#   include BOOST_PP_LOCAL_ITERATE()
#   undef FSMBASE_SET_IMPL

    template<typename T> T& get() { return pool.template acquire<T>(); }

    template<typename Event> bool processEventImpl(const Event& p_event)
    {
        TRACE("process event: [%s]", typeid(Event).name());

        bool l_handled = false;

        QFSM_UML_EXTENSIONS(
            deferralEvents.init();
        )

        QFSM_UML_EXTENSIONS(
            if (!Detail::Terminate<FsmBase>::execute(*this, p_event))
            {
                return false;
            }
        )

        QFSM_NON_UML_EXTENSIONS(
            if (!Detail::Interrupt<FsmBase>::execute(*this, p_event))
            {
                return false;
            }
        )

        QFSM_UML_EXTENSIONS(
            if (Detail::Composite<FsmBase>::execute(*this, p_event))
            {
                return true;
            }
        )

        Detail::HandleEvent<FsmBase>::execute(*this, p_event, l_handled);

        QFSM_NON_UML_EXTENSIONS(
            Detail::Else<FsmBase>::execute(*this, l_handled);
        )

        QFSM_UML_EXTENSIONS(
            deferralEvents.execute(l_handled);
            internalEvents.execute(l_handled);
            Detail::CompletionTransition<FsmBase>::execute(*this, l_handled);
        )

        return Detail::UnexpectedEvent<FsmBase>::execute(*this, p_event, l_handled);
    }

    TPool pool;
    TState currentStates[OrthogonalRegions<TDerived>::NumberOfOrthogonalRegions::value];
    QFSM_UML_EXTENSIONS(Detail::DeferralEvent<FsmBase> deferralEvents;)
    QFSM_UML_EXTENSIONS(Detail::InternalEvent<FsmBase> internalEvents;)
};

} // namespace Back
} // namespace QFsm

#endif

