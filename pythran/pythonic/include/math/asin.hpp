#ifndef PYTHONIC_INCLUDE_MATH_ASIN_HPP
#define PYTHONIC_INCLUDE_MATH_ASIN_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(asin, std::asin);
    PROXY_DECL(pythonic::math, asin);
  }
}

#endif
