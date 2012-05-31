//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_LOGGER_HPP
#define QFSM_BACK_AUX_LOGGER_HPP

#include <boost/type_traits/is_base_of.hpp>
#include <boost/mpl/find_if.hpp>

namespace QFsm
{
namespace Back
{
namespace Aux
{

class Logger { };

template<typename Pool> static typename boost::mpl::find_if<typename Pool::type, boost::is_base_of<Logger, boost::mpl::_1> >::type::type& logger(Pool& p_pool)
{
    typedef typename boost::mpl::find_if<typename Pool::type, boost::is_base_of<Logger, boost::mpl::_1> >::type::type type;
    //return p_pool.template acquire< boost::is_base_of< boost::mpl::_1, >();
}

} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

