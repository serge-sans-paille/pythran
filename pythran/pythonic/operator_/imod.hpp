#ifndef PYTHONIC_OPERATOR_IMOD_HPP
#define PYTHONIC_OPERATOR_IMOD_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            A imod(A a, B const& b) {
                return a%=b;
            }
        PROXY(pythonic::operator_, imod);
    }

}

#endif

