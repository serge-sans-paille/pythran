#ifndef PYTHONIC_NUMPY_POWER_HPP
#define PYTHONIC_NUMPY_POWER_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/pow.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_BINARY_FUNC_NAME power
#define NUMPY_BINARY_FUNC_SYM nt2::pow
#include "pythonic/types/numpy_binary_expr.hpp"
    }
}

#endif

