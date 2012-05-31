//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_CONTAINS_HPP
#define QFSM_BACK_AUX_CONTAINS_HPP

#include <boost/type_traits/is_base_of.hpp>
#include <boost/mpl/count_if.hpp>
#include <boost/mpl/or.hpp>

namespace QFsm
{
namespace Back
{
namespace Aux
{

template<typename TDerived, template<typename> class Where, typename What>
    struct Contains : boost::mpl::count_if<typename TDerived::TransitionTable, boost::is_base_of<Where<boost::mpl::_1>, What> >
{ };

template<typename TDerived, template<typename> class Where1, template<typename> class Where2, typename What>
    struct Contains2 : boost::mpl::count_if<typename TDerived::TransitionTable,
        boost::mpl::or_
        <
            boost::is_base_of<What, Where1<boost::mpl::_1> >,
            boost::is_base_of<What, Where2<boost::mpl::_1> >
        >
    >
{ };

} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

