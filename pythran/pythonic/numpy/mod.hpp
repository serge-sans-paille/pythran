#ifndef PYTHONIC_NUMPY_MOD_HPP
#define PYTHONIC_NUMPY_MOD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/operator_/mod.hpp"

namespace pythonic {

    namespace numpy {
#define NUMPY_BINARY_FUNC_NAME mod
#define NUMPY_BINARY_FUNC_SYM operator_::mod
#include "pythonic/types/numpy_binary_expr.hpp"

    }

}

#endif

