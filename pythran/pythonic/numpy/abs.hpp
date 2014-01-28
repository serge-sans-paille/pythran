#ifndef PYTHONIC_NUMPY_ABS_HPP
#define PYTHONIC_NUMPY_ABS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/abs.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::abs;

        namespace wrapper {
            PROXY(pythonic::numpy, abs)

        }
#define NUMPY_UNARY_FUNC_NAME abs
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::abs
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, abs)
    }
}

#endif

