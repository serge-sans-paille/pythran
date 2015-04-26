#ifndef PYTHONIC_INCLUDE_OPERATOR_IPOW_HPP
#define PYTHONIC_INCLUDE_OPERATOR_IPOW_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/__builtin__/pow.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            A ipow(A a, B const& b);

        PROXY_DECL(pythonic::operator_, ipow);
    }

}

#endif
