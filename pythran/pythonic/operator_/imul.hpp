#ifndef PYTHONIC_OPERATOR_IMUL_HPP
#define PYTHONIC_OPERATOR_IMUL_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            A imul(A a, B const& b) {
                return a*=b;
            }
        PROXY(pythonic::operator_, imul);
    }

}

#endif

