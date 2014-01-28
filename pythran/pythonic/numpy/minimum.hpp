#ifndef PYTHONIC_NUMPY_MINIMUM_HPP
#define PYTHONIC_NUMPY_MINIMUM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/min.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(minimum, nt2::min)

            namespace wrapper {
                PROXY(pythonic::numpy, minimum)
            }
#define NUMPY_BINARY_FUNC_NAME minimum
#define NUMPY_BINARY_FUNC_SYM wrapper::proxy::minimum
#include "pythonic/types/numpy_binary_expr.hpp"
        PROXY(pythonic::numpy, minimum)

    }

}

#endif

