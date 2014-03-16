#ifndef PYTHONIC_NUMPY_LOG1P_HPP
#define PYTHONIC_NUMPY_LOG1P_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/log1p.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME log1p
#define NUMPY_UNARY_FUNC_SYM nt2::log1p
#include "pythonic/types/numpy_unary_expr.hpp"
    }

}

#endif

