#ifndef PYTHONIC_NUMPY_FLOOR_HPP
#define PYTHONIC_NUMPY_FLOOR_HPP

#include "pythonic/utils/proxy.hpp"
#include"pythonic/types/ndarray.hpp"
#include "pythonic/types/numexpr_to_ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/floor.hpp>

namespace pythonic {

    namespace numpy {
#define NUMPY_NARY_FUNC_NAME floor
#define NUMPY_NARY_FUNC_SYM nt2::floor
#include "pythonic/types/numpy_nary_expr.hpp"

    }

}

#endif

