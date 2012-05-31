//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_VERSION_HPP
#define QFSM_VERSION_HPP

// QFSM_VERSION % 100 is the patch level
// QFSM_VERSION / 100 % 1000 is the minor version
// QFSM_VERSION / 100000 is the major version
#define QFSM_VERSION 100000

// QFSM_LIB_VERSION must be defined to be the same as QFSM_VERSION
// but as a *string* in the form "x_y[_z]" where x is the major version
// number, y is the minor version number, and z is the patch level if not 0.
#define QFSM_LIB_VERSION "1_00"

#endif

