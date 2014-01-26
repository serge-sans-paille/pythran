#ifndef PYTHONIC_NUMPY_HYPOT_HPP
#define PYTHONIC_NUMPY_HYPOT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/hypot.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::hypot;
        namespace wrapper {
            PROXY(pythonic::numpy, hypot);
        }
#define NUMPY_BINARY_FUNC_NAME hypot
#define NUMPY_BINARY_FUNC_SYM wrapper::proxy::hypot
#include "pythonic/types/numpy_binary_expr.hpp"
        PROXY(pythonic::numpy, hypot)

    }

}

#endif

