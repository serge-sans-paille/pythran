#ifndef PYTHONIC_INCLUDE_BUILTIN_COMPLEX_CONJUGATE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_COMPLEX_CONJUGATE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/conjugate.hpp"

namespace pythonic
{
  namespace __builtin__
  {
    namespace complex
    {
      USING_FUNCTOR(conjugate, numpy::functor::conjugate);
    }
  }
}
#endif
