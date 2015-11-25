#ifndef PYTHONIC_NUMPY_ARCSINH_HPP
#define PYTHONIC_NUMPY_ARCSINH_HPP

#include "pythonic/include/numpy/arcsinh.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/asinh.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME arcsinh
#define NUMPY_NARY_FUNC_SYM nt2::asinh
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
