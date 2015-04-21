#ifndef PYTHONIC_OPERATOR_TRUEDIV_HPP
#define PYTHONIC_OPERATOR_TRUEDIV_HPP

#include "pythran/pythonic/include/operator_/truediv.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            auto truediv(A const& a, B const& b) -> decltype(a/(double)b)
            {
                return a/((double)b);
            }

        PROXY_IMPL(pythonic::operator_, truediv);

    }

}

#endif
