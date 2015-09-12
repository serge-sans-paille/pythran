#ifndef PYTHONIC_INCLUDE_MATH_ACOS_HPP
#define PYTHONIC_INCLUDE_MATH_ACOS_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(acos, std::acos);
    PROXY_DECL(pythonic::math, acos);
  }
}

#endif
