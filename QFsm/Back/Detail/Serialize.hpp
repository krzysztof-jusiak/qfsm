//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_DETAIL_SERIALIZE_HPP
#define QFSM_BACK_DETAIL_SERIALIZE_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/has_xxx.hpp>
#include "QFsm/Back/Aux/Trace.hpp"

namespace QFsm
{
namespace Back
{
namespace Detail
{

class Serialize
{
    BOOST_MPL_HAS_XXX_TEMPLATE_DEF(serialize)

public:
    template<typename State, typename Pool, typename Archive>
    static void execute(const State* p_states, Pool& p_pool, Archive& p_archive)
    {
        QFSM_TRACE("serialize [current states]");
        p_archive & p_states;
        serializeTypes<typename Pool::type>(p_pool, p_archive);
    }

private:
    template<typename Seq, typename Pool, typename Archive> static void serializeTypes(Pool&, Archive&, typename boost::enable_if< boost::mpl::empty<Seq> >::type* = 0) { }
    template<typename Seq, typename Pool, typename Archive> static void serializeTypes(Pool& p_pool, Archive& p_archive, typename boost::disable_if< boost::mpl::empty<Seq> >::type* = 0)
    {
        typedef typename boost::mpl::front<Seq>::type Type;
        serializeImpl<Type>(p_pool, p_archive);
        serializeTypes<typename boost::mpl::pop_front<Seq>::type>(p_pool, p_archive);
    }

    template<typename T, typename Pool, typename Archive>
    static void serializeImpl(Pool& p_pool, Archive& p_archive, typename boost::enable_if< has_serialize<T> >::type* = 0)
    {
        QFSM_TRACE("serialize [%s]", typeid(T).name());
        p_archive & p_pool.template acquire<T>();
    }

    template<typename T, typename Pool, typename Archive>
    static void serializeImpl(Pool&, Archive&, typename boost::disable_if< has_serialize<T> >::type* = 0)
    { }
};

} // namespace Detail
} // namespace Back
} // namespace QFsm

#endif

