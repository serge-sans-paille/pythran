#ifndef PYTHONIC_OPERATOR_COUNTOF_HPP
#define PYTHONIC_OPERATOR_COUNTOF_HPP

#include "pythonic/include/operator_/countOf.hpp"

#include "pythonic/utils/proxy.hpp"
#include <algorithm>

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            long countOf(A const& a, B const& b)
            {
                return std::count(a.begin(), a.end(), b);
            }

        PROXY_IMPL(pythonic::operator_, countOf);

    }

}

#endif
