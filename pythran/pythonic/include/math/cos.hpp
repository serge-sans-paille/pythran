#ifndef PYTHONIC_INCLUDE_MATH_COS_HPP
#define PYTHONIC_INCLUDE_MATH_COS_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(cos, std::cos);
    PROXY_DECL(pythonic::math, cos);
  }
}

#endif
