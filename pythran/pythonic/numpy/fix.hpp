#ifndef PYTHONIC_NUMPY_FIX_HPP
#define PYTHONIC_NUMPY_FIX_HPP

#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/trunc.hpp>

namespace pythonic {

    namespace numpy {

#define NUMPY_UNARY_FUNC_NAME fix
#define NUMPY_UNARY_FUNC_SYM nt2::trunc
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

