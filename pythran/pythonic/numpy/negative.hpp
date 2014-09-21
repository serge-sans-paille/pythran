#ifndef PYTHONIC_NUMPY_NEGATIVE_HPP
#define PYTHONIC_NUMPY_NEGATIVE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/neg.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_UNARY_FUNC_NAME negative
    #define NUMPY_UNARY_FUNC_SYM pythonic::operator_::neg
    #include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

