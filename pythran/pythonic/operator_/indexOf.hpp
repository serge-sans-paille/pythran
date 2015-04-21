#ifndef PYTHONIC_OPERATOR_INDEXOF_HPP
#define PYTHONIC_OPERATOR_INDEXOF_HPP

#include "pythran/pythonic/include/operator_/indexOf.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            long indexOf(A const& a, B const& b)
            {
                return a.index(b);
            }

        PROXY_IMPL(pythonic::operator_, indexOf);
    }

}

#endif
