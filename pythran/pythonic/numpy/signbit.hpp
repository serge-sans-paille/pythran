#ifndef PYTHONIC_NUMPY_SIGNBIT_HPP
#define PYTHONIC_NUMPY_SIGNBIT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/bitofsign.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(signbit, nt2::bitofsign)
            namespace wrapper {
                PROXY(pythonic::numpy, signbit)

            }
#define NUMPY_UNARY_FUNC_NAME signbit
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::signbit
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, signbit)

    }

}

#endif

