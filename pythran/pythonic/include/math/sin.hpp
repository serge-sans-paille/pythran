#ifndef PYTHONIC_INCLUDE_MATH_SIN_HPP
#define PYTHONIC_INCLUDE_MATH_SIN_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(sin, std::sin);
    PROXY_DECL(pythonic::math, sin);
  }
}

#endif
