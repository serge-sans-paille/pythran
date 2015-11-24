#ifndef PYTHONIC_INCLUDE_MATH_GAMMA_HPP
#define PYTHONIC_INCLUDE_MATH_GAMMA_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    double gamma(double x);
    DECLARE_FUNCTOR(pythonic::math, gamma);
  }
}

#endif
