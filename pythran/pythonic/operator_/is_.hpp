#ifndef PYTHONIC_OPERATOR_IS_HPP
#define PYTHONIC_OPERATOR_IS_HPP

#include "pythran/pythonic/include/operator_/is_.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            auto is_(A const& a, B const& b) -> decltype(a==b)
            {
                return a==b;
            }

        PROXY_IMPL(pythonic::operator_, is_);
    }

}

#endif

