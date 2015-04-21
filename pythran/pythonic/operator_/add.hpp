#ifndef PYTHONIC_OPERATOR_ADD_HPP
#define PYTHONIC_OPERATOR_ADD_HPP

#include "pythonic/include/operator_/add.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/operator_/overloads.hpp"

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            auto add(A const& a, B const& b) -> decltype(a + b)
            {
                return a + b;
            }

        DEFINE_ALL_OPERATOR_OVERLOADS(add, +)

        PROXY_IMPL(pythonic::operator_, add);
    }

}

#endif
