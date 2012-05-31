//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_FRONT_OPERATIONS_ISFINALIZED_HPP
#define QFSM_FRONT_OPERATIONS_ISFINALIZED_HPP

#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/is_sequence.hpp>
#include "QFsm/Back/Aux/Extensions.hpp"
#include "QFsm/Back/Aux/Internal.hpp"
#include "QFsm/Back/Aux/Composite.hpp"
#include "QFsm/Back/Detail/Visitor.hpp"
#include "QFsm/Front/Operations/Finalized.hpp"

namespace QFsm
{
namespace Front
{
namespace Operations
{

QFSM_NON_UML_EXTENSIONS
(
    namespace Detail
    {

    template<typename TInitialState, typename Enable = void> struct MakeVector
    {
        typedef TInitialState type;
    };

    template<typename TInitialState> struct MakeVector<TInitialState, typename boost::disable_if< boost::mpl::is_sequence<TInitialState> >::type>
    {
        typedef boost::mpl::vector<TInitialState> type;
    };

    } // namespace Detail

    template<typename TState, typename Enable = void>
    class IsFinalized
    {
        template<bool> class IsInitialState { };

        class IsFinalizedVisitor
        {
        public:
            explicit IsFinalizedVisitor(bool& p_isFinalized)
                : m_isFinalized(p_isFinalized)
            { }

            template<typename State> void operator()() const
            {
                m_isFinalized = boost::is_base_of<Front::Operations::Finalized, State>::value;
            }

        private:
            bool& m_isFinalized;
        };

    public:
        template<typename TEvent, typename TFsm> bool operator()(const TEvent&, TFsm& p_fsm) const
        {
            typedef IsInitialState<boost::mpl::contains<typename Detail::MakeVector<typename TFsm::Derived::InitialState>::type, TState>::value> IsInitialStateType;
            return handleImpl(p_fsm, IsInitialStateType());
        }

    private:
        template<typename TFsm> bool handleImpl(TFsm& p_fsm, const IsInitialState<true>&) const
        {
            typedef typename boost::mpl::find<typename Detail::MakeVector<typename TFsm::Derived::InitialState>::type, TState>::type::pos Region;
            bool l_isFinalized = false;
            IsFinalizedVisitor l_visitor(l_isFinalized);
            Back::Detail::Visitor<TFsm>::template execute<Region>(p_fsm, l_visitor);
            return l_isFinalized;
        }

        template<typename TFsm> bool handleImpl(TFsm& p_fsm, const IsInitialState<false>&) const
        {
            BOOST_MPL_ASSERT_MSG(
                (
                    boost::mpl::contains<typename TFsm::Derived::InitialState, TState>::value
                ),
                OnFinalizedNotAllowedOnStatesDifferentFromInitialStates,
                (TState)
            );

            return false;
        }
    };

    template<typename TComposite>
    class IsFinalized<TComposite, typename boost::enable_if< boost::is_base_of<Back::Aux::Composite, TComposite> >::type> : Back::Aux::Internal
    {
        template<typename TFsm>
        class IsFinalizedVisitor
        {
        public:
            IsFinalizedVisitor(TFsm& p_fsm, bool& p_isFinalized)
                : m_fsm(p_fsm), m_isFinalized(p_isFinalized)
            { }

            template<typename State> void operator()(typename boost::enable_if< boost::is_base_of<Back::Aux::Composite, State> >::type* = 0) const
            {
                Back::Detail::Visitor<TFsm>::execute(m_fsm.template acquire<State>(), IsFinalizedVisitor<State>(m_isFinalized));
            }

            template<typename State> void operator()(typename boost::disable_if< boost::is_base_of<Back::Aux::Composite, State> >::type* = 0) const
            {
                m_isFinalized = m_isFinalized && boost::is_base_of<Front::Operations::Finalized, State>::value;
            }

        private:
            bool& m_isFinalized;
            TFsm& m_fsm;
        };

    public:
        template<typename TEvent, typename TFsm> bool operator()(const TEvent&, TFsm& p_fsm) const
        {
            bool l_isFinalized = true;
            TComposite& l_fsm = p_fsm.template acquire<TComposite>();
            IsFinalizedVisitor<TComposite> l_visitor(l_fsm, l_isFinalized);
            Back::Detail::Visitor<TFsm>::execute(l_fsm, l_visitor);
            return l_isFinalized;
        }
    };
)

} // namespace Operations
} // namespace Front
} // namespace QFsm

#endif

