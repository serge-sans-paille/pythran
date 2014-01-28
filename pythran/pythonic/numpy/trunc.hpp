#ifndef PYTHONIC_NUMPY_TRUNC_HPP
#define PYTHONIC_NUMPY_TRUNC_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/trunc.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::trunc;

        namespace wrapper {
            PROXY(pythonic::numpy, trunc)

        }
#define NUMPY_UNARY_FUNC_NAME trunc
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::trunc
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, trunc)
    }
}

#endif

