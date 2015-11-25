#ifndef PYTHONIC_NUMPY_ARCCOS_HPP
#define PYTHONIC_NUMPY_ARCCOS_HPP

#include "pythonic/include/numpy/arccos.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/acos.hpp>

namespace nt2
{
  double acos(long l)
  {
    return acos(static_cast<double>(l));
  }
}

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME arccos
#define NUMPY_NARY_FUNC_SYM nt2::acos
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
