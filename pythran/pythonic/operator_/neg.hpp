#ifndef PYTHONIC_OPERATOR_NEG_HPP
#define PYTHONIC_OPERATOR_NEG_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A>
            auto neg(A const& a) -> decltype(-a) {
                return -a;
            }
        PROXY(pythonic::operator_, neg);
    }

}

#endif

