#ifndef PYTHONIC_NUMPY_BITWISENOT_HPP
#define PYTHONIC_NUMPY_BITWISENOT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/numexpr_to_ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/types/numpy_op_helper.hpp"

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

        #define NUMPY_NARY_FUNC_NAME bitwise_not
        #define NUMPY_NARY_FUNC_SYM wrapper::bitwise_not
        #include "pythonic/types/numpy_nary_expr.hpp"
    }

}

//ndarray have to be include after as bitwise_not is used as a numpy_operator
#include"pythonic/types/ndarray.hpp"

#endif

