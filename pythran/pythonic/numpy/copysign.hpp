#ifndef PYTHONIC_NUMPY_COPYSIGN_HPP
#define PYTHONIC_NUMPY_COPYSIGN_HPP

#include "pythonic/include/numpy/copysign.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"

#include <nt2/include/functions/copysign.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME copysign
#define NUMPY_NARY_FUNC_SYM nt2::copysign
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
