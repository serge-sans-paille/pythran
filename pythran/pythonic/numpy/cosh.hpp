#ifndef PYTHONIC_NUMPY_COSH_HPP
#define PYTHONIC_NUMPY_COSH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/cosh.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::cosh;

        namespace wrapper {
            PROXY(pythonic::numpy, cosh)

        }
#define NUMPY_UNARY_FUNC_NAME cosh
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::cosh
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, cosh)

    }

}

#endif

