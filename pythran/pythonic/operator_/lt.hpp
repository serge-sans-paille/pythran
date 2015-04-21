#ifndef PYTHONIC_OPERATOR_LT_HPP
#define PYTHONIC_OPERATOR_LT_HPP

#include "pythran/pythonic/include/operator_/lt.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            auto lt(A const& a, B const& b) -> decltype(a<b) {
              return a < b ;
            }

        PROXY_IMPL(pythonic::operator_, lt);
    }

}

#endif
