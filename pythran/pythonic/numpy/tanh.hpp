#ifndef PYTHONIC_NUMPY_TANH_HPP
#define PYTHONIC_NUMPY_TANH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/tanh.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::tanh;

        namespace wrapper {
            PROXY(pythonic::numpy, tanh)

        }
#define NUMPY_UNARY_FUNC_NAME tanh
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::tanh
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, tanh)

    }

}

#endif

