#ifndef PYTHONIC_NUMPY_HYPOT_HPP
#define PYTHONIC_NUMPY_HYPOT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/hypot.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_BINARY_FUNC_NAME hypot
#define NUMPY_BINARY_FUNC_SYM nt2::hypot
#include "pythonic/types/numpy_binary_expr.hpp"

    }

}

#endif

