#ifndef PYTHONIC_NUMPY_RECIPROCAL_HPP
#define PYTHONIC_NUMPY_RECIPROCAL_HPP

#include "pythonic/include/numpy/reciprocal.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/rec.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME reciprocal
#define NUMPY_NARY_FUNC_SYM nt2::rec
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
