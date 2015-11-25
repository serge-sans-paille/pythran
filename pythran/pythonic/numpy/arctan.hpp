#ifndef PYTHONIC_NUMPY_ARCTAN_HPP
#define PYTHONIC_NUMPY_ARCTAN_HPP

#include "pythonic/include/numpy/arctan.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/atan.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME arctan
#define NUMPY_NARY_FUNC_SYM nt2::atan
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
