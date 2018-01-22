#ifndef PYTHONIC_MATH_GAMMA_HPP
#define PYTHONIC_MATH_GAMMA_HPP

#include "pythonic/include/math/gamma.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  double gamma(double x)
  {
    return std::tgamma(x);
  }

  DEFINE_FUNCTOR(pythonic::math, gamma);
}
PYTHONIC_NS_END

#endif
