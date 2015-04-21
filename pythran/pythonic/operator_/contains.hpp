#ifndef PYTHONIC_OPERATOR_CONTAINS_HPP
#define PYTHONIC_OPERATOR_CONTAINS_HPP

#include "pythran/pythonic/include/operator_/contains.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/__builtin__/in.hpp"

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            auto contains(A const& a, B const& b) -> decltype(in(a, b))
            {
                return in(a, b);
            }

        PROXY_IMPL(pythonic::operator_, contains);

    }

}

#endif
