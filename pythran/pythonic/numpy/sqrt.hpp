#ifndef PYTHONIC_NUMPY_SQRT_HPP
#define PYTHONIC_NUMPY_SQRT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

#include <nt2/include/functions/sqrt.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME sqrt
#define NUMPY_UNARY_FUNC_SYM nt2::sqrt
#include "pythonic/types/numpy_unary_expr.hpp"
    }
}

#endif

