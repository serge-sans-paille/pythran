#ifndef PYTHONIC_NUMPY_RECIPROCAL_HPP
#define PYTHONIC_NUMPY_RECIPROCAL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/rec.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME reciprocal
#define NUMPY_UNARY_FUNC_SYM nt2::rec
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

