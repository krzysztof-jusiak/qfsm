//
// Copyright (c) 2011-2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef QFSM_AUX_CONCEPT_HPP
#define QFSM_AUX_CONCEPT_HPP

namespace QFsm
{
namespace Aux
{

template<int> class AnyType { };

template<typename T>
class Concept
{
public:
    Concept()
    {
        verifyConcept = &T::conceptUsage;
    }

private:
    void (T::*verifyConcept)();
};

} // namespace Aux
} // namespace QFsm

#endif

