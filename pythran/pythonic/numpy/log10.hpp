#ifndef PYTHONIC_NUMPY_LOG10_HPP
#define PYTHONIC_NUMPY_LOG10_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/log10.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::log10;

        namespace wrapper {
            PROXY(pythonic::numpy, log10)

        }
#define NUMPY_UNARY_FUNC_NAME log10
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::log10
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, log10)

    }

}

#endif

