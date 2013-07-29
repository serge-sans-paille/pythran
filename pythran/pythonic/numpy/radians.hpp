#ifndef PYTHONIC_NUMPY_RADIANS_HPP
#define PYTHONIC_NUMPY_RADIANS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/inrad.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(radians, nt2::inrad)

            namespace wrapper {
                PROXY(pythonic::numpy, radians)

            }
#define NUMPY_UNARY_FUNC_NAME radians
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::radians
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, radians)

    }

}

#endif

