#ifndef PYTHONIC_INCLUDE_NUMPY_SIN_HPP
#define PYTHONIC_INCLUDE_NUMPY_SIN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <nt2/include/functions/sin.hpp>

namespace nt2
{
  double sin(long l);
}
namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME sin
#define NUMPY_NARY_FUNC_SYM nt2::sin
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
