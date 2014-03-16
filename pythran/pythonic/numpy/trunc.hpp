#ifndef PYTHONIC_NUMPY_TRUNC_HPP
#define PYTHONIC_NUMPY_TRUNC_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/trunc.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME trunc
#define NUMPY_UNARY_FUNC_SYM nt2::trunc
#include "pythonic/types/numpy_unary_expr.hpp"
    }
}

#endif

