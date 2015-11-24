#ifndef PYTHONIC_INCLUDE_NUMPY_FMOD_HPP
#define PYTHONIC_INCLUDE_NUMPY_FMOD_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/numpy_broadcast.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <nt2/include/functions/mod.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME fmod
#define NUMPY_NARY_FUNC_SYM nt2::mod
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif
