#ifndef PYTHONIC_NUMPY_ISINF_HPP
#define PYTHONIC_NUMPY_ISINF_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/is_inf.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(isinf, nt2::is_inf)

            namespace wrapper {
                PROXY(pythonic::numpy, isinf)

            }
#define NUMPY_UNARY_FUNC_NAME isinf
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::isinf
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, isinf)

    }

}

#endif

