#ifndef PYTHONIC_NUMPY_EXP_HPP
#define PYTHONIC_NUMPY_EXP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include <nt2/include/functions/exp.hpp>


namespace pythonic {

    namespace numpy {
#define NUMPY_UNARY_FUNC_NAME exp
#define NUMPY_UNARY_FUNC_SYM nt2::exp
#include "pythonic/types/numpy_unary_expr.hpp"

    }

}

#endif

