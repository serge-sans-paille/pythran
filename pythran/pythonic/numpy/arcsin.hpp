#ifndef PYTHONIC_NUMPY_ARCSIN_HPP
#define PYTHONIC_NUMPY_ARCSIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/asin.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(arcsin, nt2::asin)

            namespace wrapper {
                PROXY(pythonic::numpy, arcsin)

            }
#define NUMPY_UNARY_FUNC_NAME arcsin
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::arcsin
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, arcsin)
    }
}

#endif

