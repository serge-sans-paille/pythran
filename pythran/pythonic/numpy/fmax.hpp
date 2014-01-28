#ifndef PYTHONIC_NUMPY_FMAX_HPP
#define PYTHONIC_NUMPY_FMAX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/max.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(fmax, nt2::max)

            namespace wrapper {
                PROXY(pythonic::numpy, fmax)
            }
#define NUMPY_BINARY_FUNC_NAME fmax
#define NUMPY_BINARY_FUNC_SYM wrapper::proxy::fmax
#include "pythonic/types/numpy_binary_expr.hpp"
        PROXY(pythonic::numpy, fmax)

    }

}

#endif

