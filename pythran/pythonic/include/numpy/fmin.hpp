#ifndef PYTHONIC_INCLUDE_NUMPY_FMIN_HPP
#define PYTHONIC_INCLUDE_NUMPY_FMIN_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/min.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_NARY_FUNC_NAME fmin
#define NUMPY_NARY_FUNC_SYM nt2::min
#include "pythonic/include/types/numpy_nary_expr.hpp"

    }

}

#endif

