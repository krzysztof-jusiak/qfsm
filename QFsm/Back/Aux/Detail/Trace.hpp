//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_DETAIL_TRACE_HPP
#define QFSM_BACK_AUX_DETAIL_TRACE_HPP

#ifdef DEBUG_MODE
# include <typeinfo>
# include <cstdio>
# include "QFsm/Back/Aux/Detail/PrintType.hpp"
# define TRACE(...) printf("%s:%d:0: [DBG] %s: ", __FILE__, __LINE__, __FUNCTION__); printf(__VA_ARGS__); printf("\n")
# define TRACE_WRN(...) printf("%s:%d:0: [WRN] %s: ", __FILE__, __LINE__, __FUNCTION__); printf(__VA_ARGS__); printf("\n")
# define TRACE_ERR(...) printf("%s:%d:0: [ERR] %s: ", __FILE__, __LINE__, __FUNCTION__); printf(__VA_ARGS__); printf("\n")
#else
# define TRACE(...)
# define TRACE_WRN(...)
# define TRACE_ERR(...)
#endif

#endif

