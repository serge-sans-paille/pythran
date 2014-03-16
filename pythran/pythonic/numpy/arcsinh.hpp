#ifndef PYTHONIC_NUMPY_ARCSINH_HPP
#define PYTHONIC_NUMPY_ARCSINH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/asinh.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME arcsinh
#define NUMPY_UNARY_FUNC_SYM nt2::asinh
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

