#ifndef PYTHONIC_NUMPY_DEGREES_HPP
#define PYTHONIC_NUMPY_DEGREES_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/indeg.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(degrees, nt2::indeg)

            namespace wrapper {
                PROXY(pythonic::numpy, degrees)

            }
#define NUMPY_UNARY_FUNC_NAME degrees
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::degrees
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, degrees)

    }

}

#endif

