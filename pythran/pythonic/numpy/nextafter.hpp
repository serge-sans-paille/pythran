#ifndef PYTHONIC_NUMPY_NEXTAFTER_HPP
#define PYTHONIC_NUMPY_NEXTAFTER_HPP

#include "pythonic/include/numpy/nextafter.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/nextafter.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME nextafter
#define NUMPY_NARY_FUNC_SYM nt2::nextafter
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
