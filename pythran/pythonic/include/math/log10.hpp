#ifndef PYTHONIC_INCLUDE_MATH_LOG10_HPP
#define PYTHONIC_INCLUDE_MATH_LOG10_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(log10, std::log10);
    PROXY_DECL(pythonic::math, log10);
  }
}

#endif
