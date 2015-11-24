#ifndef PYTHONIC_INCLUDE_NUMPY_SPACING_HPP
#define PYTHONIC_INCLUDE_NUMPY_SPACING_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <nt2/include/functions/eps.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME spacing
#define NUMPY_NARY_FUNC_SYM nt2::eps
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
