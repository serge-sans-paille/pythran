#ifndef PYTHONIC_NUMPY_FMIN_HPP
#define PYTHONIC_NUMPY_FMIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/min.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_BINARY_FUNC_NAME fmin
#define NUMPY_BINARY_FUNC_SYM nt2::min
#include "pythonic/types/numpy_binary_expr.hpp"

    }

}

#endif

