#ifndef PYTHONIC_OPERATOR_ISNOT;_HPP
#define PYTHONIC_OPERATOR_ISNOT;_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            auto is_not(A const& a, B const& b) -> decltype(a != b) {
                return a != b;
            }
        PROXY(pythonic::operator_, is_not);
    }

}

#endif

