#ifndef PYTHONIC_NUMPY_SPACING_HPP
#define PYTHONIC_NUMPY_SPACING_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/eps.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME spacing
#define NUMPY_UNARY_FUNC_SYM nt2::eps
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

