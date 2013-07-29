#ifndef PYTHONIC_NUMPY_RINT_HPP
#define PYTHONIC_NUMPY_RINT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/iround.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(rint, nt2::iround)

            namespace wrapper {
                PROXY(pythonic::numpy, rint)

            }
#define NUMPY_UNARY_FUNC_NAME rint
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::rint
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, rint)
    }

}

#endif

