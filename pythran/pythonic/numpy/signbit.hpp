#ifndef PYTHONIC_NUMPY_SIGNBIT_HPP
#define PYTHONIC_NUMPY_SIGNBIT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/bitofsign.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME signbit
#define NUMPY_UNARY_FUNC_SYM nt2::bitofsign
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

