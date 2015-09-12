#ifndef PYTHONIC_INCLUDE_MATH_POW_HPP
#define PYTHONIC_INCLUDE_MATH_POW_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(pow, std::pow);
    PROXY_DECL(pythonic::math, pow);
  }
}

#endif
