#ifndef PYTHONIC_NUMPY_ISINF_HPP
#define PYTHONIC_NUMPY_ISINF_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/is_inf.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME isinf
#define NUMPY_UNARY_FUNC_SYM nt2::is_inf
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

