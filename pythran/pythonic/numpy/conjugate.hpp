#ifndef PYTHONIC_NUMPY_CONJUGATE_HPP
#define PYTHONIC_NUMPY_CONJUGATE_HPP

#include "pythonic/include/numpy/conjugate.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_traits.hpp"

#include <nt2/include/functions/conj.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME conjugate
#define NUMPY_NARY_FUNC_SYM nt2::conj
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
