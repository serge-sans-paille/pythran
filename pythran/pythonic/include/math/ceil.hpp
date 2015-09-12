#ifndef PYTHONIC_INCLUDE_MATH_CEIL_HPP
#define PYTHONIC_INCLUDE_MATH_CEIL_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(ceil, std::ceil);
    PROXY_DECL(pythonic::math, ceil);
  }
}

#endif
