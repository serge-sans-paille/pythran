#ifndef PYTHONIC_NUMPY_COS_HPP
#define PYTHONIC_NUMPY_COS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/cos.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::cos;

        namespace wrapper {
            PROXY(pythonic::numpy, cos)

        }
#define NUMPY_UNARY_FUNC_NAME cos
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::cos
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, cos)
    }
}

#endif

