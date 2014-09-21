#ifndef PYTHONIC_NUMPY_DIVIDE_HPP
#define PYTHONIC_NUMPY_DIVIDE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/div.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_BINARY_FUNC_NAME divide
    #define NUMPY_BINARY_FUNC_SYM pythonic::operator_::div
    #include "pythonic/types/numpy_binary_expr.hpp"

    }

}

#endif

