#ifndef PYTHONIC_OPERATOR_LT_HPP
#define PYTHONIC_OPERATOR_LT_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            auto lt(A const& a, B const& b) -> decltype(a<b) {
                return a<b;
            }
        PROXY(pythonic::operator_, lt);
    }

}

#endif

