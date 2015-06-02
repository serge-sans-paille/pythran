#ifndef PYTHONIC_MATH_SIN_HPP
#define PYTHONIC_MATH_SIN_HPP

#include "pythonic/include/math/sin.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS(sin, std::sin);
    PROXY_IMPL(pythonic::math, sin);
  }
}

#endif
