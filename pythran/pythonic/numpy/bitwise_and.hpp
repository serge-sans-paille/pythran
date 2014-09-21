#ifndef PYTHONIC_NUMPY_BITWISE_AND_HPP
#define PYTHONIC_NUMPY_BITWISE_AND_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/and_.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_BINARY_FUNC_NAME bitwise_and
    #define NUMPY_BINARY_FUNC_SYM pythonic::operator_::and_
    #include "pythonic/types/numpy_binary_expr.hpp"

    }
}

#endif

