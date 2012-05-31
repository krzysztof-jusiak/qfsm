//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_BACK_AUX_DETAIL_PRINTTYPE_HPP
#define QFSM_BACK_AUX_DETAIL_PRINTTYPE_HPP

#include <iostream>
#include <cstdlib>

#ifdef __GNUC__
# include "cxxabi.h"
#endif

namespace QFsm
{
namespace Back
{
namespace Aux
{
namespace Detail
{

namespace Detail
{

inline std::string demangle(const char* p_input)
{
#ifdef __GNUC__
    char* l_demangled = __cxxabiv1::__cxa_demangle(p_input, 0, 0, 0);
    std::string l_result(l_demangled);
    std::free(l_demangled);
    return l_result;
#else
    return std::string(p_input);
#endif
}

} // namespace Detail

template<typename T> std::string printType()
{
    return Detail::demangle(typeid(T).name());
}

template<typename T> std::string printType(const T& p_t)
{
    return Detail::demangle(typeid(p_t).name());
}

} // namespace Detail
} // namespace Aux
} // namespace Back
} // namespace QFsm

#endif

