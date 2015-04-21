#ifndef PYTHONIC_INCLUDE_OPERATOR_IXOR_HPP
#define PYTHONIC_INCLUDE_OPERATOR_IXOR_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            A ixor(A a, B const& b);

        PROXY_DECL(pythonic::operator_, ixor);
    }

}

#endif
