#ifndef PYTHONIC_OPERATOR_IAND_HPP
#define PYTHONIC_OPERATOR_IAND_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            A iand(A  a, B const& b) {
                return a&=b;
            }
        PROXY(pythonic::operator_, iand);

    }

}

#endif

