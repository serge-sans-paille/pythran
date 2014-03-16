#ifndef PYTHONIC_NUMPY_TANH_HPP
#define PYTHONIC_NUMPY_TANH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/tanh.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME tanh
#define NUMPY_UNARY_FUNC_SYM nt2::tanh
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

