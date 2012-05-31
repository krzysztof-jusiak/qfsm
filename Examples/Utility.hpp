//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <typeinfo>
#include <iostream>
#include <cassert>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#ifndef __llvm__
# include <cxxabi.h>
#endif

class e0 { };
class e1 { };
class e2 { };
class e3 { };
class e4 { };
class e5 { };
class e6 { };
class e7 { };
class e8 { };

std::string demangle(const std::string& p_mangled)
{
#ifndef __llvm__
    char* l_demangled = abi::__cxa_demangle(p_mangled.c_str(), 0, 0, 0);

    if (l_demangled)
    {
        boost::shared_ptr<char> l_result(l_demangled, std::free);
        return std::string(l_demangled);
    }
#endif

    return p_mangled;
}

std::string printType(const std::type_info& p_t)
{
    return demangle(p_t.name());
}

class ShowCurrentStateVisitor
{
public:
    ShowCurrentStateVisitor()
        : region(0)
    { }

    template<typename State> void operator()()
    {
        std::cout << "current state: [" << region++ << "] " << demangle(typeid(State).name()) << std::endl;
    }

private:
    int region;
};

#endif

