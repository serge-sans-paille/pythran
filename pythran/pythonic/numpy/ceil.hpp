#ifndef PYTHONIC_NUMPY_CEIL_HPP
#define PYTHONIC_NUMPY_CEIL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/ceil.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::ceil;

        namespace wrapper {
            PROXY(pythonic::numpy, ceil)

        }
#define NUMPY_UNARY_FUNC_NAME ceil
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::ceil
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, ceil)

    }

}

#endif

