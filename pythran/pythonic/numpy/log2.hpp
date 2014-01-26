#ifndef PYTHONIC_NUMPY_LOG2_HPP
#define PYTHONIC_NUMPY_LOG2_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/log2.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::log2;

        namespace wrapper {
            PROXY(pythonic::numpy, log2)

        }
#define NUMPY_UNARY_FUNC_NAME log2
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::log2
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, log2)

    }

}

#endif

