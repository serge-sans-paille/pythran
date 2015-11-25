#ifndef PYTHONIC_INCLUDE_BUILTIN_ABS_HPP
#define PYTHONIC_INCLUDE_BUILTIN_ABS_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/abs.hpp"

namespace pythonic
{

  namespace __builtin__
  {
    // FIXME np.abs accept any iterator while __builtin__.abs only accept
    // numeric types and numpy.array
    USING_FUNCTOR(abs, numpy::functor::abs);
  }
}

#endif
