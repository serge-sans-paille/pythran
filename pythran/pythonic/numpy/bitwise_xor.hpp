#ifndef PYTHONIC_NUMPY_BITWISE_XOR_HPP
#define PYTHONIC_NUMPY_BITWISE_XOR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/__xor__.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_BINARY_FUNC_NAME bitwise_xor
    #define NUMPY_BINARY_FUNC_SYM pythonic::operator_::__xor__
    #include "pythonic/types/numpy_binary_expr.hpp"

    }
}

#endif

