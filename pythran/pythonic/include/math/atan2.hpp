#ifndef PYTHONIC_INCLUDE_MATH_ATAN2_HPP
#define PYTHONIC_INCLUDE_MATH_ATAN2_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(atan2, std::atan2);
    PROXY_DECL(pythonic::math, atan2);
  }
}

#endif
