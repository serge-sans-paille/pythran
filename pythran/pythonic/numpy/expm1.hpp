#ifndef PYTHONIC_NUMPY_EXPM1_HPP
#define PYTHONIC_NUMPY_EXPM1_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/expm1.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::expm1;

        namespace wrapper {
            PROXY(pythonic::numpy, expm1)

        }
#define NUMPY_UNARY_FUNC_NAME expm1
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::expm1
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, expm1)

    }

}

#endif

