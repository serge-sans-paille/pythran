#ifndef PYTHONIC_NUMPY_RECIPROCAL_HPP
#define PYTHONIC_NUMPY_RECIPROCAL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/rec.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(reciprocal, nt2::rec)

            namespace wrapper {
                PROXY(pythonic::numpy, reciprocal)

            }
#define NUMPY_UNARY_FUNC_NAME reciprocal
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::reciprocal
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, reciprocal)

    }

}

#endif

