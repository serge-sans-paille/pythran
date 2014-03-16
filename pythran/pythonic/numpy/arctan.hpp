#ifndef PYTHONIC_NUMPY_ARCTAN_HPP
#define PYTHONIC_NUMPY_ARCTAN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/atan.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME arctan
#define NUMPY_UNARY_FUNC_SYM nt2::atan
#include "pythonic/types/numpy_unary_expr.hpp"
    }
}

#endif

