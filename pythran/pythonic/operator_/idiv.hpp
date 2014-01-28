#ifndef PYTHONIC_OPERATOR_IDIV_HPP
#define PYTHONIC_OPERATOR_IDIV_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            A idiv(A a, B const& b) {
                return a /= b;
            }
        PROXY(pythonic::operator_, idiv);

    }

}

#endif

