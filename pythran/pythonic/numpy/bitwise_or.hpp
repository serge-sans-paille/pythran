#ifndef PYTHONIC_NUMPY_BITWISE_OR_HPP
#define PYTHONIC_NUMPY_BITWISE_OR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/or_.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_BINARY_FUNC_NAME bitwise_or
    #define NUMPY_BINARY_FUNC_SYM pythonic::operator_::or_
    #include "pythonic/types/numpy_binary_expr.hpp"

    }
}

#endif

