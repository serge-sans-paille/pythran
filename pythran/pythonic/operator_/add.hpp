#ifndef PYTHONIC_OPERATOR_ADD_HPP
#define PYTHONIC_OPERATOR_ADD_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            auto add(A const& a, B const& b) -> decltype(a+b) {
                return a+b;
            }
        PROXY(pythonic::operator_, add);
    }

}

#endif

