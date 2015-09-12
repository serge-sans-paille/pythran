#ifndef PYTHONIC_INCLUDE_MATH_ATAN_HPP
#define PYTHONIC_INCLUDE_MATH_ATAN_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(atan, std::atan);
    PROXY_DECL(pythonic::math, atan);
  }
}

#endif
