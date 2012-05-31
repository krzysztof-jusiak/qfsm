//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_TEST_COMMON_MSGTRAITS_HPP
#define QFSM_TEST_COMMON_MSGTRAITS_HPP

#include <boost/shared_ptr.hpp>
#include <boost/mpl/int.hpp>
#include "Common/MsgTypes.hpp"

namespace QFsm
{
namespace Test
{
namespace Common
{

template<typename> class MsgTraits;

template<> struct MsgTraits<Msg1> { enum { value = 1 }; };
template<> struct MsgTraits<Msg2> { enum { value = 2 }; };
template<> struct MsgTraits<Msg3> { enum { value = 3 }; };
template<> struct MsgTraits<Msg4> { enum { value = 4 }; };
template<> struct MsgTraits<Msg5> { enum { value = 5 }; };
template<> struct MsgTraits<Msg6> { enum { value = 6 }; };
template<> struct MsgTraits<Msg7> { enum { value = 7 }; };
template<> struct MsgTraits<Msg8> { enum { value = 8 }; };
template<> struct MsgTraits<Msg9> { enum { value = 9 }; };
template<> struct MsgTraits<Msg10> { enum { value = 10 }; };
template<> struct MsgTraits<Msg11> { enum { value = 11 }; };
template<> struct MsgTraits<Msg12> { enum { value = 12 }; };
template<> struct MsgTraits<Msg13> { enum { value = 13 }; };
template<> struct MsgTraits<Msg14> { enum { value = 14 }; };
template<> struct MsgTraits<Msg15> { enum { value = 15 }; };
template<> struct MsgTraits<Msg16> { enum { value = 16 }; };

template<int> class MsgTraitsValue;

template<> struct MsgTraitsValue<1> : boost::mpl::int_<1> { typedef Msg1 type; };
template<> struct MsgTraitsValue<2> : boost::mpl::int_<2> { typedef Msg2 type; };
template<> struct MsgTraitsValue<3> : boost::mpl::int_<3> { typedef Msg3 type; };
template<> struct MsgTraitsValue<4> : boost::mpl::int_<4> { typedef Msg4 type; };
template<> struct MsgTraitsValue<5> : boost::mpl::int_<5> { typedef Msg5 type; };
template<> struct MsgTraitsValue<6> : boost::mpl::int_<6> { typedef Msg6 type; };
template<> struct MsgTraitsValue<7> : boost::mpl::int_<7> { typedef Msg7 type; };
template<> struct MsgTraitsValue<8> : boost::mpl::int_<8> { typedef Msg8 type; };
template<> struct MsgTraitsValue<9> : boost::mpl::int_<9> { typedef Msg9 type; };
template<> struct MsgTraitsValue<10> : boost::mpl::int_<10> { typedef Msg10 type; };
template<> struct MsgTraitsValue<11> : boost::mpl::int_<11> { typedef Msg11 type; };
template<> struct MsgTraitsValue<12> : boost::mpl::int_<12> { typedef Msg12 type; };
template<> struct MsgTraitsValue<13> : boost::mpl::int_<13> { typedef Msg13 type; };
template<> struct MsgTraitsValue<14> : boost::mpl::int_<14> { typedef Msg14 type; };
template<> struct MsgTraitsValue<15> : boost::mpl::int_<15> { typedef Msg15 type; };
template<> struct MsgTraitsValue<16> : boost::mpl::int_<16> { typedef Msg16 type; };

template<int id> boost::shared_ptr<int> createEvent()
{
    return boost::shared_ptr<int>(new int(id));
}

} // namespace Common
} // namespace Test
} // namespace QFsm

#endif

