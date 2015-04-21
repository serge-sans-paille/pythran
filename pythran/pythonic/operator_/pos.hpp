#ifndef PYTHONIC_OPERATOR_POS_HPP
#define PYTHONIC_OPERATOR_POS_HPP

#include "pythran/pythonic/include/operator_/pos.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A>
            auto pos(A const& a) -> decltype(+a)
            {
                return +a;
            }

        PROXY_IMPL(pythonic::operator_, pos);
    }

}

#endif
