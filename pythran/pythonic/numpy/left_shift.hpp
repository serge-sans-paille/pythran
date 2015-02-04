#ifndef PYTHONIC_NUMPY_LEFT_SHIFT_HPP
#define PYTHONIC_NUMPY_LEFT_SHIFT_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/operator_/lshift.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"

namespace pythonic {

    namespace numpy {

    #define NUMPY_NARY_FUNC_NAME left_shift
    #define NUMPY_NARY_FUNC_SYM pythonic::operator_::lshift
    #include "pythonic/types/numpy_nary_expr.hpp"

    }

}

#endif

