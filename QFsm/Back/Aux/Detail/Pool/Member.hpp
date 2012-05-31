//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_DETAIL_MEMBER_HPP
#define QFSM_BACK_AUX_DETAIL_MEMBER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>

namespace QFsm
{
namespace Back
{
namespace Aux
{
namespace Detail
{
namespace Pool
{

template<typename, typename = void> class Member;

template<typename T> struct StackAllocator { typedef T type; };

template<typename T>
class Member< StackAllocator<T>, typename boost::enable_if< boost::has_trivial_constructor<T> >::type>
{
public:
    typedef T& type;

    Member() { }

    explicit Member(T& p_member)
        : m_member(p_member)
    { }

    void set(T& p_new) { m_member = p_new; }
    T& get() { return m_member; }
    T& acquire() { return m_member; }

private:
    T m_member;
};

template<typename T>
class Member< StackAllocator<T>, typename boost::disable_if< boost::has_trivial_constructor<T> >::type>
{
public:
    typedef T& type;

    explicit Member(T& p_member = T())
        : m_member(p_member)
    { }

    void set(T& p_new) { m_member = p_new; }
    T& get() { return m_member; }
    T& acquire() { return m_member; }

private:
    T& m_member;
};

template<typename T>
class Member< boost::shared_ptr<T> >
{
public:
    typedef boost::shared_ptr<T> type;

    explicit Member(type p_member = type(new T))
        : m_member(p_member)
    { }

    void set(type p_new) { m_member = p_new; }
    type get() { return m_member; }
    T& acquire() { return *m_member; }

private:
    type m_member;
};

} // namespace Pool
} // namespace Detail
} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

