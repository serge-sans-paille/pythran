#ifndef PYTHONIC_NUMPY_SIN_HPP
#define PYTHONIC_NUMPY_SIN_HPP

#include "pythonic/include/numpy/sin.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/sin.hpp>

namespace nt2
{
  double sin(long l)
  {
    return sin(static_cast<double>(l));
  }
}

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME sin
#define NUMPY_NARY_FUNC_SYM nt2::sin
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
