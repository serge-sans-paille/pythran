#ifndef PYTHONIC_NUMPY_ISNAN_HPP
#define PYTHONIC_NUMPY_ISNAN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/is_nan.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(isnan, nt2::is_nan)
            namespace wrapper {
                PROXY(pythonic::numpy, isnan)

            }
#define NUMPY_UNARY_FUNC_NAME isnan
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::isnan
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, isnan)

    }

}

#endif

