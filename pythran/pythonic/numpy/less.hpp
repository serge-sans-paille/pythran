#ifndef PYTHONIC_NUMPY_LESS_HPP
#define PYTHONIC_NUMPY_LESS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/lt.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_BINARY_FUNC_NAME less
    #define NUMPY_BINARY_FUNC_SYM pythonic::operator_::lt
    #include "pythonic/types/numpy_binary_expr.hpp"

    }

}

#endif

