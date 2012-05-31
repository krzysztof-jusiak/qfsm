//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_EXTENSIONS_HPP
#define QFSM_BACK_AUX_EXTENSIONS_HPP

#ifdef __GNUC__
# pragma GCC system_header
#endif

#if defined(QFSM_EXTENSIONS_UML)
# define QFSM_UML_EXTENSIONS(...) __VA_ARGS__
# define QFSM_UML_EXTENSIONS_ELSE(...)
#else
# define QFSM_UML_EXTENSIONS(...)
# define QFSM_UML_EXTENSIONS_ELSE(...) __VA_ARGS__
#endif

#if defined(QFSM_EXTENSIONS_NON_UML)
# define QFSM_NON_UML_EXTENSIONS(...) __VA_ARGS__
# define QFSM_NON_UML_EXTENSIONS_ELSE(...)
#else
# define QFSM_NON_UML_EXTENSIONS(...)
# define QFSM_NON_UML_EXTENSIONS_ELSE(...) __VA_ARGS__
#endif

#endif

