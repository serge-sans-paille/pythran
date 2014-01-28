#ifndef PYTHONIC_OPERATOR_INDEXOF;_HPP
#define PYTHONIC_OPERATOR_INDEXOF;_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            long indexOf(A const& a, B const& b) {
                return a.index(b);
            }
        PROXY(pythonic::operator_, indexOf);
    }

}

#endif

