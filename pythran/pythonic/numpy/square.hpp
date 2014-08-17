#ifndef PYTHONIC_NUMPY_SQUARE_HPP
#define PYTHONIC_NUMPY_SQUARE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/sqr.hpp>

namespace pythonic {

    namespace numpy {

#define NUMPY_UNARY_FUNC_NAME square
#define NUMPY_UNARY_FUNC_SYM nt2::sqr
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

