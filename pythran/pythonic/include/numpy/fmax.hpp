#ifndef PYTHONIC_INCLUDE_NUMPY_FMAX_HPP
#define PYTHONIC_INCLUDE_NUMPY_FMAX_HPP

#include <nt2/include/functions/max.hpp>

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/numpy_broadcast.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME fmax
#define NUMPY_NARY_FUNC_SYM nt2::max
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
