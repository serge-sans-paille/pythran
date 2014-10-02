#ifndef PYTHONIC_NUMPY_INVERT_HPP
#define PYTHONIC_NUMPY_INVERT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/operator_/invert.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_UNARY_FUNC_NAME invert
    #define NUMPY_UNARY_FUNC_SYM operator_::invert
    #include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

