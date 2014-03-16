#ifndef PYTHONIC_NUMPY_FLOOR_HPP
#define PYTHONIC_NUMPY_FLOOR_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/floor.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME floor
#define NUMPY_UNARY_FUNC_SYM nt2::floor
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

