//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_CACHE_HPP
#define QFSM_BACK_AUX_CACHE_HPP

#include <boost/optional.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/bool.hpp>
#include "QFsm/Back/FsmPolicy.hpp"
#include "QFsm/Back/Aux/TransitionTypes.hpp"

namespace QFsm
{
namespace Back
{
namespace Aux
{

namespace Detail { class Cache_ { }; } // namespace Detail

template<typename TTransitionTable, typename TCacheEnabled>
class Cache : Detail::Cache_
{
    struct Guards : boost::mpl::transform_view
        <
            TTransitionTable,
            Aux::Guard<boost::mpl::_2>
        >::type
    { };

    template<typename T> struct Optional
    {
        typedef Optional type;
        typedef boost::optional<bool> element_type;
        element_type field;
    };

    struct Entries : boost::mpl::inherit_linearly
        <
            Guards,
            boost::mpl::inherit< boost::mpl::_1, Optional<boost::mpl::_2> >
        >::type
    { };

public:
    void reset()
    {
        fillTypes<Guards>();
    }

    template<typename T> void set(bool p_value)
    {
        get<T, Optional>(m_entries) = p_value;
    }

    template<typename T> boost::optional<bool> get()
    {
        return get<T, Optional>(m_entries);
    }

private:
    template<typename T> inline typename Optional<T>::element_type& get(Optional<T>& p_arg)
    {
        return p_arg.field;
    }

    template<typename Seq> void fillTypes(typename boost::enable_if< boost::mpl::empty<Seq> >::type* = 0) { }
    template<typename Seq> void fillTypes(typename boost::disable_if< boost::mpl::empty<Seq> >::type* = 0)
    {
        get<typename boost::mpl::front<Seq>::type, Optional>(m_entries);
        fillTypes<typename boost::mpl::pop_front<Seq>::type>();
    }

    Entries m_entries;
};

template<typename TTransitionTable> class Cache<TTransitionTable, CacheDisabled> : Detail::Cache_
{
public:
    void reset() { }
    template<typename T> void set(bool) { }
    template<typename T> boost::mpl::false_ get() { return boost::mpl::false_(); }
};

template<typename Pool> static typename boost::mpl::find_if<typename Pool::type, boost::is_base_of<Detail::Cache_, boost::mpl::_1> >::type::type& cache(Pool& p_pool)
{
    typedef typename boost::mpl::find_if<typename Pool::type, boost::is_base_of<Detail::Cache_, boost::mpl::_1> >::type::type type;
    return p_pool.template acquire<type>();
}

} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

