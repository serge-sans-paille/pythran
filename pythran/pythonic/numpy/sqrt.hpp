#ifndef PYTHONIC_NUMPY_SQRT_HPP
#define PYTHONIC_NUMPY_SQRT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

#include <nt2/include/functions/sqrt.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::sqrt;

        namespace wrapper {
            PROXY(pythonic::numpy, sqrt)

        }
#define NUMPY_UNARY_FUNC_NAME sqrt
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::sqrt
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, sqrt)
    }
}

#endif

