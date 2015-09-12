#ifndef PYTHONIC_INCLUDE_MATH_ASINH_HPP
#define PYTHONIC_INCLUDE_MATH_ASINH_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(asinh, std::asinh);
    PROXY_DECL(pythonic::math, asinh);
  }
}

#endif
