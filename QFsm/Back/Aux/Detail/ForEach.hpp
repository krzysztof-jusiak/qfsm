//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_DETAIL_FOREACH_HPP
#define QFSM_BACK_AUX_DETAIL_FOREACH_HPP

#include <boost/mpl/empty.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/front.hpp>
#include <boost/utility/enable_if.hpp>

namespace QFsm
{
namespace Back
{
namespace Aux
{
namespace Detail
{

/**
 * low debug size 'for each' through given types
 */
template<typename Seq, typename F> inline static void forEach(F, typename boost::enable_if< boost::mpl::empty<Seq> >::type* = 0) { }
template<typename Seq, typename F> inline static void forEach(F p_f, typename boost::disable_if< boost::mpl::empty<Seq> >::type* = 0)
{
    p_f.template operator()<typename boost::mpl::front<Seq>::type>();
    forEach<typename boost::mpl::pop_front<Seq>::type>(p_f);
}

} // namespace Detail
} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

