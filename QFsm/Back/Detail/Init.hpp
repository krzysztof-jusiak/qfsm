//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_INIT_HPP
#define QFSM_BACK_DETAIL_INIT_HPP

#include <boost/utility/enable_if.hpp>
#include "QFsm/Back/Aux/Detail/Trace.hpp"
#include "QFsm/Back/Detail/OrthogonalRegions.hpp"
#include "QFsm/Back/Aux/State.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{

template<typename TFsmBase>
class Init
{
    typedef typename OrthogonalRegions<typename TFsmBase::Derived>::template ForEachRegion<> ForEachRegion;

    template<typename = typename OrthogonalRegions<typename TFsmBase::Derived>::NumberOfOrthogonalRegions, bool dummy = false>
    class InitImpl
    {
    public:
        template<typename Region> static void execute(TFsmBase& p_fsm)
        {
            TRACE("init [%d]", Region::value);
            typedef boost::mpl::int_<Region::value + OrthogonalRegions<typename TFsmBase::Derived>::OneRegion::value> NextRegion;
            Aux::State<typename TFsmBase::State, typename TFsmBase::Fsm>::init(p_fsm.currentStates[Region::value], NextRegion());
        }
    };

    template<bool dummy>
    class InitImpl<typename OrthogonalRegions<typename TFsmBase::Derived>::OneRegion, dummy>
    {
    public:
        template<typename Region> static void execute(TFsmBase& p_fsm)
        {
            TRACE("init [%d]", int(Region::value));
            Aux::State<typename TFsmBase::State, typename TFsmBase::Fsm>::init(p_fsm.currentStates[Region::value], Region());
        }
    };

public:
    static void execute(TFsmBase& p_fsm)
    {
        TRACE("Number of orthogonal regions: %d", OrthogonalRegions<typename TFsmBase::Derived>::NumberOfOrthogonalRegions::value);
        ForEachRegion::template execute< InitImpl<> >(p_fsm);
    }
};

} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

