#ifndef PYTHONIC_NUMPY_CEIL_HPP
#define PYTHONIC_NUMPY_CEIL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/ceil.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME ceil
#define NUMPY_UNARY_FUNC_SYM nt2::ceil
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

