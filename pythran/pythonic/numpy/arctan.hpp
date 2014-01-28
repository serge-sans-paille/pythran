#ifndef PYTHONIC_NUMPY_ARCTAN_HPP
#define PYTHONIC_NUMPY_ARCTAN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/atan.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(arctan, nt2::atan)

            namespace wrapper {
                PROXY(pythonic::numpy, arctan)

            }
#define NUMPY_UNARY_FUNC_NAME arctan
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::arctan
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, arctan)
    }
}

#endif

