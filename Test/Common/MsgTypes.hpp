//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_TEST_COMMON_MSGTYPES_HPP
#define QFSM_TEST_COMMON_MSGTYPES_HPP

namespace QFsm
{
namespace Test
{
namespace Common
{

struct Msg1 { enum { value = 1 }; explicit Msg1(int data = 1) : data(data) { } int data; };
struct Msg2 { enum { value = 2 }; explicit Msg2(int data = 2) : data(data) { } int data; };
struct Msg3 { enum { value = 3 }; explicit Msg3(int data = 3) : data(data) { } int data; };
struct Msg4 { enum { value = 4 }; explicit Msg4(int data = 4) : data(data) { } int data; };
struct Msg5 { enum { value = 5 }; explicit Msg5(int data = 5) : data(data) { } int data; };
struct Msg6 { enum { value = 6 }; explicit Msg6(int data = 6) : data(data) { } int data; };
struct Msg7 { enum { value = 7 }; explicit Msg7(int data = 7) : data(data) { } int data; };
struct Msg8 { enum { value = 8 }; explicit Msg8(int data = 8) : data(data) { } int data; };
struct Msg9 { enum { value = 9 }; explicit Msg9(int data = 9) : data(data) { } int data; };
struct Msg10 { enum { value = 10 }; explicit Msg10(int data = 10) : data(data) { } int data; };
struct Msg11 { enum { value = 11 }; explicit Msg11(int data = 11) : data(data) { } int data; };
struct Msg12 { enum { value = 12 }; explicit Msg12(int data = 12) : data(data) { } int data; };
struct Msg13 { enum { value = 13 }; explicit Msg13(int data = 13) : data(data) { } int data; };
struct Msg14 { enum { value = 14 }; explicit Msg14(int data = 14) : data(data) { } int data; };
struct Msg15 { enum { value = 15 }; explicit Msg15(int data = 15) : data(data) { } int data; };
struct Msg16 { enum { value = 16 }; explicit Msg16(int data = 16) : data(data) { } int data; };

} // namespace Common
} // namespace Test
} // namespace QFsm

#endif

