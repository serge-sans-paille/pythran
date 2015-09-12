#ifndef PYTHONIC_INCLUDE_MATH_EXPM1_HPP
#define PYTHONIC_INCLUDE_MATH_EXPM1_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(expm1, std::expm1);
    PROXY_DECL(pythonic::math, expm1);
  }
}

#endif
