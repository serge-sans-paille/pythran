#ifndef PYTHONIC_NUMPY_SIGN_HPP
#define PYTHONIC_NUMPY_SIGN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/sign.hpp>

namespace pythonic {

    namespace numpy {
        using nt2::sign;

        namespace wrapper {
            PROXY(pythonic::numpy, sign)

        }
#define NUMPY_UNARY_FUNC_NAME sign
#define NUMPY_UNARY_FUNC_SYM wrapper::proxy::sign
#include "pythonic/types/numpy_unary_expr.hpp"
        PROXY(pythonic::numpy, sign)

    }

}

#endif

