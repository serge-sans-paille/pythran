#ifndef PYTHONIC_NUMPY_BITWISENOT_HPP
#define PYTHONIC_NUMPY_BITWISENOT_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace numpy {

        template <class A>
            decltype(~std::declval<A const&>()) bitwise_not(A const& a) {
                return ~a;
            }

            bool bitwise_not(bool t0) {
                return not t0;
            }

        PROXY(pythonic::numpy, bitwise_not);
    }

}

#endif

