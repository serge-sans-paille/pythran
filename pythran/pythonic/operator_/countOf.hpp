#ifndef PYTHONIC_OPERATOR_COUNTOF_HPP
#define PYTHONIC_OPERATOR_COUNTOF_HPP

#include "pythonic/utils/proxy.hpp"
#include <algorithm>

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            long countOf(A const& a, B const& b) {
                return std::count(a.begin(), a.end(), b);
            }
        PROXY(pythonic::operator_, countOf);

    }

}

#endif

