#ifndef PYTHONIC_NUMPY_FMAX_HPP
#define PYTHONIC_NUMPY_FMAX_HPP

#include "pythonic/include/numpy/fmax.hpp"

#include <nt2/include/functions/max.hpp>

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME fmax
#define NUMPY_NARY_FUNC_SYM nt2::max
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
