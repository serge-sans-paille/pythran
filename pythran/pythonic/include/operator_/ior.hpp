#ifndef PYTHONIC_INCLUDE_OPERATOR_IOR_HPP
#define PYTHONIC_INCLUDE_OPERATOR_IOR_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            A ior(A a, B const& b);

        PROXY_DECL(pythonic::operator_, ior);
    }

}

#endif
