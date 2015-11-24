#ifndef PYTHONIC_NUMPY_FMOD_HPP
#define PYTHONIC_NUMPY_FMOD_HPP

#include "pythonic/include/numpy/fmod.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"

#include <nt2/include/functions/mod.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME fmod
#define NUMPY_NARY_FUNC_SYM nt2::mod
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif
