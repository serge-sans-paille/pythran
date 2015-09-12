#ifndef PYTHONIC_INCLUDE_MATH_GAMMA_HPP
#define PYTHONIC_INCLUDE_MATH_GAMMA_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    double gamma(double x);
    PROXY_DECL(pythonic::math, gamma);
  }
}

#endif
