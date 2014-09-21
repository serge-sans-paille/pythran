#ifndef PYTHONIC_NUMPY_EQUAL_HPP
#define PYTHONIC_NUMPY_EQUAL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/eq.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_BINARY_FUNC_NAME equal
    #define NUMPY_BINARY_FUNC_SYM pythonic::operator_::eq
    #include "pythonic/types/numpy_binary_expr.hpp"

    }

}

#endif

