#ifndef PYTHONIC_NUMPY_FABS_HPP
#define PYTHONIC_NUMPY_FABS_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numexpr_to_ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/abs.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_NARY_FUNC_NAME fabs
#define NUMPY_NARY_FUNC_SYM nt2::abs
#include "pythonic/types/numpy_nary_expr.hpp"

    }

}

#endif

