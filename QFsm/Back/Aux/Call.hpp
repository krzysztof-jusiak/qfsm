//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_CALL_HPP
#define QFSM_BACK_AUX_CALL_HPP

#include <boost/type_traits/is_base_of.hpp>
#include "QFsm/Back/Aux/Internal.hpp"
#include "QFsm/Front/Operations/None.hpp"

namespace QFsm
{
namespace Back
{
namespace Aux
{

template<typename Result, typename TAction> class Call
{
    template<bool = boost::is_base_of<Internal, TAction>::value> class IsInternal { };
    template<bool = boost::is_base_of<Front::Operations::None, TAction>::value> class IsNone { };

public:
    template<typename TEvent, typename TFsm>
    static Result inline execute(const TEvent& p_event, TFsm& p_fsm)
    {
        return executeImpl(p_event, p_fsm, IsInternal<>(), IsNone<>());
    }

private:
    template<typename TEvent, typename TFsm>
    static Result inline executeImpl(const TEvent&,
                                     TFsm&,
                                     const IsInternal<false>&,
                                     const IsNone<true>&)
    {
        return Result();
    }

    template<typename TEvent, typename TFsm>
    static Result inline executeImpl(const TEvent&,
                                     TFsm&,
                                     const IsInternal<true>&,
                                     const IsNone<true>&)
    {
        return Result();
    }

    template<typename TEvent, typename TFsm>
    static Result inline executeImpl(const TEvent& p_event,
                                     TFsm& p_fsm,
                                     const IsInternal<false>&,
                                     const IsNone<false>&)
    {
        TFsm::Log::template onActionExecuted<TAction>(p_fsm.pool);
        return *(p_fsm.pool.template acquire<TAction>())(p_event);
    }

    template<typename TEvent, typename TFsm>
    static Result inline executeImpl(const TEvent& p_event,
                                     TFsm& p_fsm,
                                     const IsInternal<true>&,
                                     const IsNone<false>&)
    {
        TFsm::Log::template onActionExecuted<TAction>(p_fsm.pool);
        return TAction()(p_event, p_fsm);
    }
};

template<typename TGuard> class Call<bool, TGuard>
{
    template<bool = boost::is_base_of<Internal, TGuard>::value> class IsInternal { };
    template<bool = boost::is_base_of<Front::Operations::None, TGuard>::value> class IsNone { };

public:
    template<typename TEvent, typename TFsm>
    static bool inline execute(const TEvent& p_event, TFsm& p_fsm)
    {
        return executeImpl(p_event, p_fsm, IsInternal<>(), IsNone<>());
    }

private:
    template<typename TEvent, typename TFsm>
    static bool inline executeImpl(const TEvent&,
                                   TFsm&,
                                   const IsInternal<false>&,
                                   const IsNone<true>&)
    {
        return true;
    }

    template<typename TEvent, typename TFsm>
    static bool inline executeImpl(const TEvent&,
                                   TFsm&,
                                   const IsInternal<true>&,
                                   const IsNone<true>&)
    {
        return true;
    }

    template<typename TEvent, typename TFsm>
    static bool inline executeImpl(const TEvent& p_event,
                                   TFsm& p_fsm,
                                   const IsInternal<false>&,
                                   const IsNone<false>&)
    {
        TFsm::Log::template onGuardExecuted<TGuard>(p_fsm.pool);
        return (p_fsm.pool.template acquire<TGuard>())(p_event);
    }

    template<typename TEvent, typename TFsm>
    static bool inline executeImpl(const TEvent& p_event,
                                   TFsm& p_fsm,
                                   const IsInternal<true>&,
                                   const IsNone<false>&)
    {
        TFsm::Log::template onGuardExecuted<TGuard>(p_fsm.pool);
        return TGuard()(p_event, p_fsm);
    }
};

template<typename TAction> class Call<void, TAction>
{
    template<bool = boost::is_base_of<Internal, TAction>::value> class IsInternal { };
    template<bool = boost::is_base_of<Front::Operations::None, TAction>::value> class IsNone { };

public:
    template<typename TEvent, typename TFsm>
    static void inline execute(const TEvent& p_event, TFsm& p_fsm)
    {
        executeImpl(p_event, p_fsm, IsInternal<>(), IsNone<>());
    }

private:
    template<typename TEvent, typename TFsm>
    static void inline executeImpl(const TEvent&,
                                   TFsm&,
                                   const IsInternal<false>&,
                                   const IsNone<true>&)
    { }

    template<typename TEvent, typename TFsm>
    static void inline executeImpl(const TEvent&,
                                   TFsm&,
                                   const IsInternal<true>&,
                                   const IsNone<true>&)
    { }

    template<typename TEvent, typename TFsm>
    static void inline executeImpl(const TEvent& p_event,
                                   TFsm& p_fsm,
                                   const IsInternal<false>&,
                                   const IsNone<false>&)
    {
        TFsm::Log::template onActionExecuted<TAction>(p_fsm.pool);
        (p_fsm.pool.template acquire<TAction>())(p_event);
    }


    template<typename TEvent, typename TFsm>
    static void inline executeImpl(const TEvent& p_event,
                                   TFsm& p_fsm,
                                   const IsInternal<true>&,
                                   const IsNone<false>&)
    {
        TFsm::Log::template onActionExecuted<TAction>(p_fsm.pool);
        TAction()(p_event, p_fsm);
    }
};

} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

