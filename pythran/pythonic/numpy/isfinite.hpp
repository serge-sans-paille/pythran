#ifndef PYTHONIC_NUMPY_ISFINITE_HPP
#define PYTHONIC_NUMPY_ISFINITE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/is_finite.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(isfinite, nt2::is_finite)

            namespace wrapper {
                PROXY(pythonic::numpy, isfinite)

            }
#define NUMPY_UNARY_FUNC_NAME isfinite
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::isfinite
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, isfinite)

    }

}

#endif

