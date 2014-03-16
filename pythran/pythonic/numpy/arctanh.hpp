#ifndef PYTHONIC_NUMPY_ARCTANH_HPP
#define PYTHONIC_NUMPY_ARCTANH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/atanh.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME arctanh
#define NUMPY_UNARY_FUNC_SYM nt2::atanh
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

