#ifndef PYTHONIC_NUMPY_FMIN_HPP
#define PYTHONIC_NUMPY_FMIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/min.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(fmin, nt2::min)

            namespace wrapper {
                PROXY(pythonic::numpy, fmin)
            }
#define NUMPY_BINARY_FUNC_NAME fmin
#define NUMPY_BINARY_FUNC_SYM wrapper::proxy::fmin
#include "pythonic/types/numpy_binary_expr.hpp"
        PROXY(pythonic::numpy, fmin)

    }

}

#endif

