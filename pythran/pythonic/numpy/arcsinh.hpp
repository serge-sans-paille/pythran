#ifndef PYTHONIC_NUMPY_ARCSINH_HPP
#define PYTHONIC_NUMPY_ARCSINH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/asinh.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(arcsinh, nt2::asinh)

            namespace wrapper {
                PROXY(pythonic::numpy, arcsinh)
            }
#define NUMPY_UNARY_FUNC_NAME arcsinh
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::arcsinh
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, arcsinh)

    }

}

#endif

