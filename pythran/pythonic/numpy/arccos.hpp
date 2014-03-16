#ifndef PYTHONIC_NUMPY_ARCCOS_HPP
#define PYTHONIC_NUMPY_ARCCOS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/acos.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME arccos
#define NUMPY_UNARY_FUNC_SYM nt2::acos
#include "pythonic/types/numpy_unary_expr.hpp"
    }
}

#endif

