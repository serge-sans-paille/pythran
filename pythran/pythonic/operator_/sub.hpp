#ifndef PYTHONIC_OPERATOR_SUB_HPP
#define PYTHONIC_OPERATOR_SUB_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/operator_/overloads.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            auto sub(A const& a, B const& b) -> decltype(a-b) {
                return a-b;
            }
        DEFINE_ALL_OPERATOR_OVERLOADS(sub,-)
        PROXY(pythonic::operator_, sub);
    }

}

#endif

