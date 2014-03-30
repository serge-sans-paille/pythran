#ifndef PYTHONIC_NUMPY_ARCCOSH_HPP
#define PYTHONIC_NUMPY_ARCCOSH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/acosh.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME arccosh
#define NUMPY_UNARY_FUNC_SYM nt2::acosh
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

