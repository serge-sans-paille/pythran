#ifndef PYTHONIC_NUMPY_DEG2RAD_HPP
#define PYTHONIC_NUMPY_DEG2RAD_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/inrad.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(deg2rad, nt2::inrad)

            namespace wrapper {
                PROXY(pythonic::numpy, deg2rad)

            }
#define NUMPY_UNARY_FUNC_NAME deg2rad
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::deg2rad
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, deg2rad)
    }

}

#endif

