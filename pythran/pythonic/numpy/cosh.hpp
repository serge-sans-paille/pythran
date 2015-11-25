#ifndef PYTHONIC_NUMPY_COSH_HPP
#define PYTHONIC_NUMPY_COSH_HPP

#include "pythonic/include/numpy/cosh.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"

#include <nt2/include/functions/cosh.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME cosh
#define NUMPY_NARY_FUNC_SYM nt2::cosh
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
