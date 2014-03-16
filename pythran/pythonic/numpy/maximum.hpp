#ifndef PYTHONIC_NUMPY_MAXIMUM_HPP
#define PYTHONIC_NUMPY_MAXIMUM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/max.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_BINARY_FUNC_NAME maximum
#define NUMPY_BINARY_FUNC_SYM nt2::max
#include "pythonic/types/numpy_binary_expr.hpp"

    }

}

#endif

