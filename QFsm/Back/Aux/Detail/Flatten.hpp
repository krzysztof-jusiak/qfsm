//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_DETAIL_FLATTEN_HPP
#define QFSM_BACK_AUX_DETAIL_FLATTEN_HPP

#include <boost/mpl/vector.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/back_inserter.hpp>

namespace QFsm
{
namespace Back
{
namespace Aux
{
namespace Detail
{

template<class Sequence> struct Flatten : boost::mpl::fold
    <
        Sequence,
        boost::mpl::vector0<>,
        boost::mpl::copy
        <
            boost::mpl::if_
            <
                boost::mpl::is_sequence<boost::mpl::_2>,
                boost::mpl::_2,
                typename boost::mpl::vector<boost::mpl::_2>::type
            >,
            boost::mpl::back_inserter<boost::mpl::_1>
        >
    >
{ };

} // namespace Detail
} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

