#ifndef PYTHONIC_NUMPY_SINH_HPP
#define PYTHONIC_NUMPY_SINH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/sinh.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME sinh
#define NUMPY_UNARY_FUNC_SYM nt2::sinh
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

