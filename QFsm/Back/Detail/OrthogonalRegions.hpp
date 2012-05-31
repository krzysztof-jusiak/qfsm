//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_ORTHOGONALREGIONS_HPP
#define QFSM_BACK_DETAIL_ORTHOGONALREGIONS_HPP

#include <boost/mpl/int.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/size.hpp>

namespace QFsm
{
namespace Back
{

template<typename TDerived>
class OrthogonalRegions
{
public:
    typedef boost::mpl::int_<1> OneRegion;
    typedef boost::mpl::int_<0> FirstRegion;

    QFSM_UML_EXTENSIONS
    (
        struct GetNumberOfOrthogonalRegions : boost::mpl::if_
            <
                boost::mpl::is_sequence<typename TDerived::InitialState>,
                boost::mpl::size<typename TDerived::InitialState>,
                boost::mpl::int_<1>
            >
        { };

        typedef boost::mpl::int_<GetNumberOfOrthogonalRegions::type::value> NumberOfOrthogonalRegions;
    )

    QFSM_UML_EXTENSIONS_ELSE(
        typedef OneRegion NumberOfOrthogonalRegions;
    )

    template<typename Size = NumberOfOrthogonalRegions, typename Region = FirstRegion, bool dummy = false> class ForEachRegion
    {
        typedef boost::mpl::int_<Region::value + OneRegion::value> NextRegion;

    public:
        template<typename T, typename Arg1> static void execute(Arg1& p_arg1)
        {
            T::template execute<Region>(p_arg1);
            ForEachRegion<Size, NextRegion>::template execute<T>(p_arg1);
        }

        template<typename T, typename Arg1, typename Arg2> static void execute(Arg1& p_arg1, Arg2& p_arg2)
        {
            T::template execute<Region>(p_arg1, p_arg2);
            ForEachRegion<Size, NextRegion>::template execute<T>(p_arg1, p_arg2);
        }

        template<typename T, typename Arg1, typename Arg2, typename Arg3> static void execute(Arg1& p_arg1, Arg2& p_arg2, Arg3& p_arg3)
        {
            T::template execute<Region>(p_arg1, p_arg2, p_arg3);
            ForEachRegion<Size, NextRegion>::template execute<T>(p_arg1, p_arg2, p_arg3);
        }
    };

    template<bool dummy> class ForEachRegion<OneRegion, FirstRegion, dummy>
    {
    public:
        template<typename T, typename Arg1> static void execute(Arg1& p_arg1)
        {
            T::template execute<FirstRegion>(p_arg1);
        }

        template<typename T, typename Arg1, typename Arg2> static void execute(Arg1& p_arg1, Arg2& p_arg2)
        {
            T::template execute<FirstRegion>(p_arg1, p_arg2);
        }

        template<typename T, typename Arg1, typename Arg2, typename Arg3> static void execute(Arg1& p_arg1, Arg2& p_arg2, Arg3& p_arg3)
        {
            T::template execute<FirstRegion>(p_arg1, p_arg2, p_arg3);
        }
    };

    template<bool dummy> class ForEachRegion<NumberOfOrthogonalRegions, NumberOfOrthogonalRegions, dummy>
    {
    public:
        template<typename T, typename Arg1> static void execute(Arg1&) { }
        template<typename T, typename Arg1, typename Arg2> static void execute(Arg1&, Arg2&) { }
        template<typename T, typename Arg1, typename Arg2, typename Arg3> static void execute(Arg1&, Arg2&, Arg3&) { }
    };
};

} // namespace Back
} // namespace QFsm

#endif

