#ifndef PYTHONIC_NUMPY_SINH_HPP
#define PYTHONIC_NUMPY_SINH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/sinh.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::sinh;

        namespace wrapper {
            PROXY(pythonic::numpy, sinh)

        }
#define NUMPY_UNARY_FUNC_NAME sinh
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::sinh
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, sinh)

    }

}

#endif

