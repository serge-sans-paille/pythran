#ifndef PYTHONIC_OPERATOR_INVERT_HPP
#define PYTHONIC_OPERATOR_INVERT_HPP

#include "pythran/pythonic/include/operator_/invert.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A>
            decltype(~std::declval<A const&>()) invert(A const& a)
            {
                return ~a;
            }

        PROXY_IMPL(pythonic::operator_, invert);
    }

}

#endif
