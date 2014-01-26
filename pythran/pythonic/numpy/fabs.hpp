#ifndef PYTHONIC_NUMPY_FABS_HPP
#define PYTHONIC_NUMPY_FABS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/abs.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(fabs, nt2::abs)

            namespace wrapper {
                PROXY(pythonic::numpy, fabs)

            }
#define NUMPY_UNARY_FUNC_NAME fabs
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::fabs
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, fabs)

    }

}

#endif

