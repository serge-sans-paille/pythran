#ifndef PYTHONIC_NUMPY_SPACING_HPP
#define PYTHONIC_NUMPY_SPACING_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/eps.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(spacing, nt2::eps)
            namespace wrapper {
                PROXY(pythonic::numpy, spacing)

            }
#define NUMPY_UNARY_FUNC_NAME spacing
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::spacing
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, spacing)

    }

}

#endif

