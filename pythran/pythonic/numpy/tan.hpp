#ifndef PYTHONIC_NUMPY_TAN_HPP
#define PYTHONIC_NUMPY_TAN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/tan.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::tan;

        namespace wrapper {
            PROXY(pythonic::numpy, tan)

        }
#define NUMPY_UNARY_FUNC_NAME tan
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::tan
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, tan)
    }
}

#endif

