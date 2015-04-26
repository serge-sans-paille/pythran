#ifndef PYTHONIC_OPERATOR_IOR_HPP
#define PYTHONIC_OPERATOR_IOR_HPP

#include "pythran/pythonic/include/operator_/ior.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            A ior(A a, B const& b)
            {
                return a|=b;
            }

        PROXY_IMPL(pythonic::operator_, ior);
    }

}

#endif
