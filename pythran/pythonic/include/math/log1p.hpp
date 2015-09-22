#ifndef PYTHONIC_INCLUDE_MATH_LOG1P_HPP
#define PYTHONIC_INCLUDE_MATH_LOG1P_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(log1p, std::log1p);
    PROXY_DECL(pythonic::math, log1p);
  }
}

#endif
