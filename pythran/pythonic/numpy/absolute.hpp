#ifndef PYTHONIC_NUMPY_ABSOLUTE_HPP
#define PYTHONIC_NUMPY_ABSOLUTE_HPP

#include "pythonic/numpy/abs.hpp"

namespace pythonic {

    namespace numpy {

#define NUMPY_NARY_FUNC_NAME absolute
#define NUMPY_NARY_FUNC_SYM nt2::abs
#include "pythonic/types/numpy_nary_expr.hpp"

    }
}

#endif

