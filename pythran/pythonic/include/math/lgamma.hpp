#ifndef PYTHONIC_INCLUDE_MATH_LGAMMA_HPP
#define PYTHONIC_INCLUDE_MATH_LGAMMA_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(lgamma, std::lgamma);
    PROXY_DECL(pythonic::math, lgamma);
  }
}

#endif
