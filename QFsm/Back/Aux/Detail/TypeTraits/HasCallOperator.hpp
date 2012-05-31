//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_DETAIL_TYPETRAITS_HASCALLOPERATOR_HPP
#define QFSM_BACK_AUX_DETAIL_TYPETRAITS_HASCALLOPERATOR_HPP

#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/non_type.hpp>

namespace QFsm
{
namespace Back
{
namespace Aux
{
namespace Detail
{
namespace TypeTraits
{

namespace Detail
{
template<typename T> class void_exp_result { };
template<typename T, typename U> U const& operator,(U const&, void_exp_result<T>);
template<typename T, typename U> U& operator,(U&, void_exp_result<T>);
template<typename, typename Dst> struct clone_constness { typedef Dst type; };
template<typename Src, typename Dst> struct clone_constness<const Src, Dst> { typedef const Dst type; };
} // namespace Detail

template<typename Type, typename TCall>
struct HasCallOperator
{
    template<typename Derived> class HasCallOperatorMember
    {
        class BaseMixin
        {
        public:
            void operator()() { }
        };

        struct Base : public Derived, public BaseMixin { };

        template<typename T> static boost::mpl::aux::no_tag deduce(T*, boost::non_type<void (BaseMixin::*)(), &T::operator()>* = 0);
        static boost::mpl::aux::yes_tag deduce(...);

    public:
        static const bool value = sizeof(boost::mpl::aux::yes_tag) == sizeof(deduce((Base*)(0)));
    };

    struct Derived : public Type
    {
        using Type::operator();
        boost::mpl::aux::no_tag operator()(...) const;
    };

    typedef typename Detail::clone_constness<Type, Derived>::type type;

    template<typename T, typename U> struct ReturnValue
    {
        static boost::mpl::aux::yes_tag deduce(U);
        static boost::mpl::aux::no_tag deduce(...);
        static boost::mpl::aux::no_tag deduce(boost::mpl::aux::no_tag);
        static boost::mpl::aux::no_tag deduce(Detail::void_exp_result<T>);
    };

    template<typename T> struct ReturnValue<T, void>
    {
        static boost::mpl::aux::yes_tag deduce(...);
        static boost::mpl::aux::no_tag deduce(boost::mpl::aux::no_tag);
    };

    template<bool, typename> struct Impl
    {
        static const bool value = false;
    };

    template<typename T, typename U> struct Impl<true, U(const T&)>
    {
        static const bool value = sizeof(ReturnValue<Type, T>::deduce((((type*)0)->operator()(*(T*)0), Detail::void_exp_result<Type>()))) == sizeof(boost::mpl::aux::yes_tag);
    };

public:
   static const bool value = Impl<HasCallOperatorMember<Type>::value, TCall>::value;
};

} // namespace TypeTraits
} // namespace Detail
} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

