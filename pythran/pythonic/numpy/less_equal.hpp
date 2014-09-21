#ifndef PYTHONIC_NUMPY_LESSEQUAL_HPP
#define PYTHONIC_NUMPY_LESSEQUAL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/le.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_BINARY_FUNC_NAME less_equal
    #define NUMPY_BINARY_FUNC_SYM pythonic::operator_::le
    #include "pythonic/types/numpy_binary_expr.hpp"

    }

}

#endif

