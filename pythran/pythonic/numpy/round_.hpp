#ifndef PYTHONIC_NUMPY_ROUND_HPP
#define PYTHONIC_NUMPY_ROUND_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/iround2even.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME round_
#define NUMPY_UNARY_FUNC_SYM nt2::iround2even
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

