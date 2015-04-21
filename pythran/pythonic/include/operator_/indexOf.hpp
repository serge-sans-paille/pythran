#ifndef PYTHONIC_INCLUDE_OPERATOR_INDEXOF_HPP
#define PYTHONIC_INCLUDE_OPERATOR_INDEXOF_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            long indexOf(A const& a, B const& b)
            {
                return a.index(b);
            }

        PROXY_DECL(pythonic::operator_, indexOf);
    }

}

#endif
