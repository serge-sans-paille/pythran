#ifndef PYTHONIC_NUMPY_REMAINDER_HPP
#define PYTHONIC_NUMPY_REMAINDER_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/remainder.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::remainder;

        namespace wrapper {
            PROXY(pythonic::numpy, remainder)

        }
#define NUMPY_BINARY_FUNC_NAME remainder
#define NUMPY_BINARY_FUNC_SYM wrapper::proxy::remainder
#include "pythonic/types/numpy_binary_expr.hpp"
        PROXY(pythonic::numpy, remainder)

    }

}

#endif

