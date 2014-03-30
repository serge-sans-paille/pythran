#ifndef PYTHONIC_NUMPY_SIGN_HPP
#define PYTHONIC_NUMPY_SIGN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/sign.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME sign
#define NUMPY_UNARY_FUNC_SYM nt2::sign
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

