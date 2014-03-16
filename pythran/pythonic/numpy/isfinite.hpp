#ifndef PYTHONIC_NUMPY_ISFINITE_HPP
#define PYTHONIC_NUMPY_ISFINITE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/is_finite.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME isfinite
#define NUMPY_UNARY_FUNC_SYM nt2::is_finite
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

