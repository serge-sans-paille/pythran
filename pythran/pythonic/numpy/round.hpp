#ifndef PYTHONIC_NUMPY_ROUND_HPP
#define PYTHONIC_NUMPY_ROUND_HPP

#include "pythonic/numpy/rint.hpp"

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME round
#define NUMPY_UNARY_FUNC_SYM nt2::iround
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

