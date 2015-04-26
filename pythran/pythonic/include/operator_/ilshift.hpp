#ifndef PYTHONIC_INCLUDE_OPERATOR_ILSHIFT_HPP
#define PYTHONIC_INCLUDE_OPERATOR_ILSHIFT_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            A ilshift(A a, B const& b);

        PROXY_DECL(pythonic::operator_, ilshift);
    }

}

#endif
