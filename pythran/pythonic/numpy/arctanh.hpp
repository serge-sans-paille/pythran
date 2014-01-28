#ifndef PYTHONIC_NUMPY_ARCTANH_HPP
#define PYTHONIC_NUMPY_ARCTANH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/atanh.hpp>

namespace pythonic {

    namespace numpy {
        ALIAS(arctanh, nt2::atanh)

            namespace wrapper {
                PROXY(pythonic::numpy, arctanh)
            }
#define NUMPY_UNARY_FUNC_NAME arctanh
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::arctanh
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, arctanh)

    }

}

#endif

