#ifndef PYTHONIC_NUMPY_ARCTAN2_HPP
#define PYTHONIC_NUMPY_ARCTAN2_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/atan2.hpp>

namespace pythonic {

    namespace numpy {

#define NUMPY_BINARY_FUNC_NAME arctan2
#define NUMPY_BINARY_FUNC_SYM nt2::atan2
#include "pythonic/types/numpy_binary_expr.hpp"

    }

}

#endif

