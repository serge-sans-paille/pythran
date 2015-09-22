#ifndef PYTHONIC_INCLUDE_MATH_TAN_HPP
#define PYTHONIC_INCLUDE_MATH_TAN_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(tan, std::tan);
    PROXY_DECL(pythonic::math, tan);
  }
}

#endif
