#ifndef PYTHONIC_OPERATOR_INVERT_HPP
#define PYTHONIC_OPERATOR_INVERT_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace operator_ {

        template <class A>
            decltype(~std::declval<A const&>()) invert(A const& a) {
                return ~a;
            }
        PROXY(pythonic::operator_, invert);
    }

}

#endif

