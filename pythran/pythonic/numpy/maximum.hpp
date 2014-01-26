#ifndef PYTHONIC_NUMPY_MAXIMUM_HPP
#define PYTHONIC_NUMPY_MAXIMUM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/max.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(maximum, nt2::max)

            namespace wrapper {
                PROXY(pythonic::numpy, maximum)
            }
#define NUMPY_BINARY_FUNC_NAME maximum
#define NUMPY_BINARY_FUNC_SYM wrapper::proxy::maximum
#include "pythonic/types/numpy_binary_expr.hpp"
        PROXY(pythonic::numpy, maximum)

    }

}

#endif

