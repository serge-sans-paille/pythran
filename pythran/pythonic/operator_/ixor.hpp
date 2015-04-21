#ifndef PYTHONIC_OPERATOR_IXOR_HPP
#define PYTHONIC_OPERATOR_IXOR_HPP

#include "pythran/pythonic/include/operator_/ixor.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            A ixor(A a, B const& b)
            {
                return a^=b;
            }

        PROXY_IMPL(pythonic::operator_, ixor);
    }

}

#endif
