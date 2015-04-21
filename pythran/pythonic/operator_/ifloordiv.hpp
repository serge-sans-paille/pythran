#ifndef PYTHONIC_OPERATOR_IFLOORDIV_HPP
#define PYTHONIC_OPERATOR_IFLOORDIV_HPP

#include "pythran/pythonic/include/operator_/ifloordiv.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A, class B>
            A ifloordiv(A a, B const& b)
            {
                A tmp = (a-(a % b))/b;
                a = tmp;
                return tmp;
            }

        PROXY_IMPL(pythonic::operator_, ifloordiv);
    }

}

#endif
