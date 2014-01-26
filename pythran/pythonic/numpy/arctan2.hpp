#ifndef PYTHONIC_NUMPY_ARCTAN2_HPP
#define PYTHONIC_NUMPY_ARCTAN2_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/atan2.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(arctan2, nt2::atan2)

            namespace wrapper {
                PROXY(pythonic::numpy, arctan2)

            }
#define NUMPY_BINARY_FUNC_NAME arctan2
#define NUMPY_BINARY_FUNC_SYM wrapper::proxy::arctan2
#include "pythonic/types/numpy_binary_expr.hpp"
        PROXY(pythonic::numpy, arctan2)

    }

}

#endif

