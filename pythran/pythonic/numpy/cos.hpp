#ifndef PYTHONIC_NUMPY_COS_HPP
#define PYTHONIC_NUMPY_COS_HPP

#include "pythonic/include/numpy/cos.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/cos.hpp>

namespace nt2
{
  double cos(long l)
  {
    return cos(static_cast<double>(l));
  }
}

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME cos
#define NUMPY_NARY_FUNC_SYM nt2::cos
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
