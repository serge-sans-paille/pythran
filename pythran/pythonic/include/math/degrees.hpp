#ifndef PYTHONIC_INCLUDE_MATH_DEGREES_HPP
#define PYTHONIC_INCLUDE_MATH_DEGREES_HPP

#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace math
  {

    template <class T>
    double degrees(T x);

    DECLARE_FUNCTOR(pythonic::math, degrees);
  }
}

#endif
