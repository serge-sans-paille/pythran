#ifndef PYTHONIC_NUMPY_SPACING_HPP
#define PYTHONIC_NUMPY_SPACING_HPP

#include "pythonic/include/numpy/spacing.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/eps.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME spacing
#define NUMPY_NARY_FUNC_SYM nt2::eps
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
