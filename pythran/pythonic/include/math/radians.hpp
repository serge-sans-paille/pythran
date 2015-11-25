#ifndef PYTHONIC_INCLUDE_MATH_RADIANS_HPP
#define PYTHONIC_INCLUDE_MATH_RADIANS_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/math/pi.hpp"

namespace pythonic
{

  namespace math
  {
    template <class T>
    double radians(T x);
    DECLARE_FUNCTOR(pythonic::math, radians);
  }
}

#endif
