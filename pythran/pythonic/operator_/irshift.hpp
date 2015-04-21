#ifndef PYTHONIC_OPERATOR_IRSHIFT_HPP
#define PYTHONIC_OPERATOR_IRSHIFT_HPP

#include "pythran/pythonic/include/operator_/irshift.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            A irshift(A a, B const& b)
            {
                return a>>=b;
            }

        PROXY_IMPL(pythonic::operator_, irshift);
    }

}

#endif
