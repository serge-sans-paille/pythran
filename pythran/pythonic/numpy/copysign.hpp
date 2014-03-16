#ifndef PYTHONIC_NUMPY_COPYSIGN_HPP
#define PYTHONIC_NUMPY_COPYSIGN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/copysign.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_BINARY_FUNC_NAME copysign
#define NUMPY_BINARY_FUNC_SYM nt2::copysign
#include "pythonic/types/numpy_binary_expr.hpp"
    }
}

#endif

