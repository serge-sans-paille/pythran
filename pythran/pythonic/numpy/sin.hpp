#ifndef PYTHONIC_NUMPY_SIN_HPP
#define PYTHONIC_NUMPY_SIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/sin.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::sin;

        namespace wrapper {
            PROXY(pythonic::numpy, sin)

        }
#define NUMPY_UNARY_FUNC_NAME sin
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::sin
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, sin)
    }
}

#endif

