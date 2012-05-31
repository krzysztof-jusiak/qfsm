//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_OPERATIONS_ISFINISHED_HPP
#define QFSM_FRONT_OPERATIONS_ISFINISHED_HPP

#include <boost/type_traits/is_base_of.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/assert.hpp>
#include "QFsm/Back/Aux/Internal.hpp"
#include "QFsm/Back/Aux/FsmType.hpp"
#include "QFsm/Front/Operations/Finish.hpp"

namespace QFsm
{
namespace Front
{
namespace Operations
{

/**
 *
 */
template<typename TState>
class IsFinished : Back::Aux::Internal
{
    template<bool = boost::is_base_of<Back::Aux::FsmType, TState>::value> class IsComposite { };
    template<bool> class IsInitialState { };

    class IsFinishedVisitor
    {
    public:
        explicit IsFinishedVisitor(bool& p_isFinished)
            : m_isFinished(p_isFinished)
        { }

        template<typename State> void operator()() const
        {
            //if is fsm recurency
            m_isFinished = m_isFinished && boost::is_base_of<Front::Operations::Finish, State>::value;
        }

    private:
        bool& m_isFinished;
    };

public:
    template<typename TEvent, typename TFsm> bool operator()(const TEvent&, TFsm& p_fsm) const
    {
        return handleImpl(p_fsm, IsComposite<>());
    }

private:
    template<typename TFsm> bool handleImpl(TFsm& p_fsm, const IsComposite<true>&) const
    {
        bool l_isFinished = true;
        p_fsm.template visitCurrentStates<IsFinishedVisitor>(l_isFinished);
        return l_isFinished;
    }

    template<typename TFsm> bool handleImpl(TFsm& p_fsm, const IsComposite<false>&) const
    {
        typedef IsInitialState<boost::mpl::contains<typename TFsm::Derived::InitialState, TState>::value> IsInitialStateType;
        return handleImpl(p_fsm, IsInitialStateType());
    }

    template<typename TFsm> bool handleImpl(TFsm&, const IsInitialState<true>&) const
    {
        //bool l_isFinished = true;
        //typedef typename boost::mpl::find<typename TFsm::Derived::InitialState, TState>::type::pos Region;
    //template<typename Region, typename Visitor> void visitCurrentState(Visitor p_visitor)
    //{
        ////Visit::template execute<Region, Visitor>(*this, p_visitor);
    //}
        //p_fsm.template visitCurrentState<Region>(IsFinishedVisitor(l_isFinished));
        //return l_isFinished;
        return true;
    }

    template<typename TFsm> bool handleImpl(TFsm& p_fsm, const IsInitialState<false>&) const
    {
        BOOST_MPL_ASSERT_MSG(
            (
                boost::mpl::contains<typename TFsm::Derived::InitialState, TState>::value
            ),
            OnFinishNotAllowedOnStatesDifferentFromInitialStates,
            (TState)
        );

        return false;
    }
};

} // namespace Operations
} // namespace Front
} // namespace QFsm

#endif

