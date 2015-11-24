#ifndef PYTHONIC_INCLUDE_NUMPY_COS_HPP
#define PYTHONIC_INCLUDE_NUMPY_COS_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <nt2/include/functions/cos.hpp>

namespace nt2
{
  double cos(long l);
}

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME cos
#define NUMPY_NARY_FUNC_SYM nt2::cos
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
