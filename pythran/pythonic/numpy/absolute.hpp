#ifndef PYTHONIC_NUMPY_ABSOLUTE_HPP
#define PYTHONIC_NUMPY_ABSOLUTE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/abs.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME absolute
#define NUMPY_UNARY_FUNC_SYM nt2::abs
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

