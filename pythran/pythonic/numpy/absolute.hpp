#ifndef PYTHONIC_NUMPY_ABSOLUTE_HPP
#define PYTHONIC_NUMPY_ABSOLUTE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/abs.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(absolute, nt2::abs)
            namespace wrapper {
                PROXY(pythonic::numpy, absolute)

            }
#define NUMPY_UNARY_FUNC_NAME absolute
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::absolute
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, absolute)

    }

}

#endif

