#ifndef PYTHONIC_NUMPY_RAD2DEG_HPP
#define PYTHONIC_NUMPY_RAD2DEG_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/indeg.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(rad2deg, nt2::indeg)

            namespace wrapper {
                PROXY(pythonic::numpy, rad2deg)

            }
#define NUMPY_UNARY_FUNC_NAME rad2deg
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::rad2deg
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, rad2deg)

    }

}

#endif

