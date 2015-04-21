#ifndef PYTHONIC_OPERATOR_ILSHIFT_HPP
#define PYTHONIC_OPERATOR_ILSHIFT_HPP

#include "pythran/pythonic/include/operator_/ilshift.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            A ilshift(A a, B const& b)
            {
                return a <<= b;
            }
        PROXY_IMPL(pythonic::operator_, ilshift);
    }

}

#endif
