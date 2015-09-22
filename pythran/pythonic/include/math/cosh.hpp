#ifndef PYTHONIC_INCLUDE_MATH_COSH_HPP
#define PYTHONIC_INCLUDE_MATH_COSH_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(cosh, std::cosh);
    PROXY_DECL(pythonic::math, cosh);
  }
}

#endif
