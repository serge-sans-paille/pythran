#ifndef PYTHONIC_NUMPY_RAD2DEG_HPP
#define PYTHONIC_NUMPY_RAD2DEG_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/indeg.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME rad2deg
#define NUMPY_UNARY_FUNC_SYM nt2::indeg
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

