#ifndef PYTHONIC_NUMPY_BITWISENOT_HPP
#define PYTHONIC_NUMPY_BITWISENOT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/invert.hpp"

namespace pythonic {

    namespace numpy {

        bool bitwise_not(bool t0) {
            return not t0;
        }

        template <class A>
            decltype(~std::declval<A const&>()) bitwise_not(A const& a) {
                return ~a;
            }

        PROXY(pythonic::numpy, bitwise_not)
    }

}

#endif

