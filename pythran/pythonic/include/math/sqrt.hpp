#ifndef PYTHONIC_INCLUDE_MATH_SQRT_HPP
#define PYTHONIC_INCLUDE_MATH_SQRT_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(sqrt, std::sqrt);
    PROXY_DECL(pythonic::math, sqrt);
  }
}

#endif
