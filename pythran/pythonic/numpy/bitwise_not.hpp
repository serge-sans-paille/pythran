#ifndef PYTHONIC_NUMPY_BITWISENOT_HPP
#define PYTHONIC_NUMPY_BITWISENOT_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {
    namespace numpy {

        namespace wrapper {
            template <class A>
                decltype(~std::declval<A const&>()) bitwise_not(A const& a) {
                    return ~a;
                }

            bool bitwise_not(bool t0) {
                return not t0;
            }

        }

        #define NUMPY_UNARY_FUNC_NAME bitwise_not
        #define NUMPY_UNARY_FUNC_SYM wrapper::bitwise_not
        #include "pythonic/types/numpy_unary_expr.hpp"
    }

}

#endif

