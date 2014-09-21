#ifndef PYTHONIC_NUMPY_LOGICALNOT_HPP
#define PYTHONIC_NUMPY_LOGICALNOT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/not_.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_UNARY_FUNC_NAME logical_not
    #define NUMPY_UNARY_FUNC_SYM pythonic::operator_::not_
    #include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

