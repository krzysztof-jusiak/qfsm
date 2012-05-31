//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_AUX_TRACE_HPP
#define QFSM_AUX_TRACE_HPP

#ifdef QFSM_DEBUG_MODE
# include <typeinfo>
# include <cstdio>
# define QFSM_TRACE(...) printf("%s:%d:0: [DBG] %s: ", __FILE__, __LINE__, __FUNCTION__); printf(__VA_ARGS__); printf("\n")
# define QFSM_TRACE_WRN(...) printf("%s:%d:0: [WRN] %s: ", __FILE__, __LINE__, __FUNCTION__); printf(__VA_ARGS__); printf("\n")
# define QFSM_TRACE_ERR(...) printf("%s:%d:0: [ERR] %s: ", __FILE__, __LINE__, __FUNCTION__); printf(__VA_ARGS__); printf("\n")
# define QFSM_UNUSED(...) __VA_ARGS__
#else
# define QFSM_TRACE(...)
# define QFSM_TRACE_WRN(...)
# define QFSM_TRACE_ERR(...)
# define QFSM_UNUSED(...)
#endif

#endif

