#ifndef PYTHONIC_OPERATOR_IRSHIFT_HPP
#define PYTHONIC_OPERATOR_IRSHIFT_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            A irshift(A a, B const& b) {
                return a>>=b;
            }
        PROXY(pythonic::operator_, irshift);
    }

}

#endif

