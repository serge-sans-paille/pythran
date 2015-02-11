#ifndef PYTHONIC_NUMPY_FABS_HPP
#define PYTHONIC_NUMPY_FABS_HPP

#include "pythonic/numpy/abs.hpp"

namespace pythonic {

    namespace numpy {

#define NUMPY_NARY_FUNC_NAME fabs
#define NUMPY_NARY_FUNC_SYM nt2::abs
#include "pythonic/types/numpy_nary_expr.hpp"

    }
}

#endif
