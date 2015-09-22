#ifndef PYTHONIC_INCLUDE_MATH_ISNAN_HPP
#define PYTHONIC_INCLUDE_MATH_ISNAN_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(isnan, std::isnan);
    PROXY_DECL(pythonic::math, isnan);
  }
}

#endif
