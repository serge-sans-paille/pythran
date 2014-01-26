#ifndef PYTHONIC_OPERATOR_ISUB_HPP
#define PYTHONIC_OPERATOR_ISUB_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            A isub(A a, B const& b) {
                return a-=b;
            }
        PROXY(pythonic::operator_, isub);
    }

}

#endif

