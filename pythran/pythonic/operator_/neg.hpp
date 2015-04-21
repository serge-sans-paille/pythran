#ifndef PYTHONIC_OPERATOR_NEG_HPP
#define PYTHONIC_OPERATOR_NEG_HPP

#include "pythran/pythonic/include/operator_/neg.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A>
            auto neg(A const& a) -> decltype(-a)
            {
                return -a;
            }

        PROXY_IMPL(pythonic::operator_, neg);
    }

}

#endif
