#ifndef PYTHONIC_NUMPY_ARCSIN_HPP
#define PYTHONIC_NUMPY_ARCSIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/asin.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME arcsin
#define NUMPY_UNARY_FUNC_SYM nt2::asin
#include "pythonic/types/numpy_unary_expr.hpp"
    }
}

#endif

