#ifndef PYTHONIC_NUMPY_CONJUGATE_HPP
#define PYTHONIC_NUMPY_CONJUGATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/conj.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(conjugate, nt2::conj)

            namespace wrapper {
                PROXY(pythonic::numpy, conjugate)

            }
#define NUMPY_UNARY_FUNC_NAME conjugate
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::conjugate
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, conjugate)

    }

}

#endif

