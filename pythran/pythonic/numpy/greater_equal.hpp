#ifndef PYTHONIC_NUMPY_GREATEREQUAL_HPP
#define PYTHONIC_NUMPY_GREATEREQUAL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/ge.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_BINARY_FUNC_NAME greater_equal
    #define NUMPY_BINARY_FUNC_SYM pythonic::operator_::ge
    #include "pythonic/types/numpy_binary_expr.hpp"

    }

}

#endif

