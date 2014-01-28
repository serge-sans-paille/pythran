#ifndef PYTHONIC_NUMPY_LDEXP_HPP
#define PYTHONIC_NUMPY_LDEXP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/ldexp.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::ldexp;

        namespace wrapper {
            PROXY(pythonic::numpy, ldexp)
        }
#define NUMPY_BINARY_FUNC_NAME ldexp
#define NUMPY_BINARY_FUNC_SYM wrapper::proxy::ldexp
#include "pythonic/types/numpy_binary_expr.hpp"
        PROXY(pythonic::numpy, ldexp)

    }

}

#endif

