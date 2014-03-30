#ifndef PYTHONIC_NUMPY_MOD_HPP
#define PYTHONIC_NUMPY_MOD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/mod.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_BINARY_FUNC_NAME mod
#define NUMPY_BINARY_FUNC_SYM nt2::mod
#include "pythonic/types/numpy_binary_expr.hpp"

    }

}

#endif

