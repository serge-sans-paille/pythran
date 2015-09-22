#ifndef PYTHONIC_INCLUDE_MATH_COPYSIGN_HPP
#define PYTHONIC_INCLUDE_MATH_COPYSIGN_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(copysign, std::copysign);
    PROXY_DECL(pythonic::math, copysign);
  }
}

#endif
