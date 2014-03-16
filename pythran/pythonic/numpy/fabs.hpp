#ifndef PYTHONIC_NUMPY_FABS_HPP
#define PYTHONIC_NUMPY_FABS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/abs.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME fabs
#define NUMPY_UNARY_FUNC_SYM nt2::abs
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

