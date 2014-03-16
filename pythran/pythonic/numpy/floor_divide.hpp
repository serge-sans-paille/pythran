#ifndef PYTHONIC_NUMPY_FLOORDIVIDE_HPP
#define PYTHONIC_NUMPY_FLOORDIVIDE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/divfloor.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_BINARY_FUNC_NAME floor_divide
#define NUMPY_BINARY_FUNC_SYM nt2::divfloor
#include "pythonic/types/numpy_binary_expr.hpp"

    }

}

#endif

