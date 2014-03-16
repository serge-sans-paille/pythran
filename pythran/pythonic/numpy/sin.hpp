#ifndef PYTHONIC_NUMPY_SIN_HPP
#define PYTHONIC_NUMPY_SIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/sin.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME sin
#define NUMPY_UNARY_FUNC_SYM nt2::sin
#include "pythonic/types/numpy_unary_expr.hpp"
    }
}

#endif

