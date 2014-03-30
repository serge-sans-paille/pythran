#ifndef PYTHONIC_NUMPY_REMAINDER_HPP
#define PYTHONIC_NUMPY_REMAINDER_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/remainder.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_BINARY_FUNC_NAME remainder
#define NUMPY_BINARY_FUNC_SYM nt2::remainder
#include "pythonic/types/numpy_binary_expr.hpp"
    }

}

#endif

