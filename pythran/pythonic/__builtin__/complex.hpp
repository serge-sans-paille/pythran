#ifndef PYTHONIC_BUILTIN_COMPLEX_HPP
#define PYTHONIC_BUILTIN_COMPLEX_HPP

#include "pythonic/include/__builtin__/complex.hpp"

#include "pythonic/types/complex.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace functor
  {
    complex::type complex::operator()(double v0, double v1) const
    {
      return {v0, v1};
    }
  }
}
PYTHONIC_NS_END

#endif
