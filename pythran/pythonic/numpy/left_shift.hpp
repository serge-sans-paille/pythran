#ifndef PYTHONIC_NUMPY_LEFT_SHIFT_HPP
#define PYTHONIC_NUMPY_LEFT_SHIFT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/operator_/lshift.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_BINARY_FUNC_NAME left_shift
    #define NUMPY_BINARY_FUNC_SYM pythonic::operator_::lshift
    #include "pythonic/types/numpy_binary_expr.hpp"

    }

}

#endif

