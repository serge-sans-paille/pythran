#ifndef PYTHONIC_OPERATOR_CONTAINS_HPP
#define PYTHONIC_OPERATOR_CONTAINS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/__builtin__/in.hpp"

namespace pythonic {

    namespace operator_ {
        template <class A, class B>
            auto contains(A const& a, B const& b) -> decltype(in(a, b)){
                return in(a, b);
            }
        PROXY(pythonic::operator_, contains);

    }

}

#endif

