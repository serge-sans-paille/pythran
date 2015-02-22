#ifndef PYTHONIC_NUMPY_BITWISE_XOR_HPP
#define PYTHONIC_NUMPY_BITWISE_XOR_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/operator_/__xor__.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_NARY_FUNC_NAME bitwise_xor
    #define NUMPY_NARY_FUNC_SYM pythonic::operator_::__xor__
    #include "pythonic/types/numpy_nary_expr.hpp"

    }
}

#endif

