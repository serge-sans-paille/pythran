#ifndef PYTHONIC_INCLUDE_MATH_ATANH_HPP
#define PYTHONIC_INCLUDE_MATH_ATANH_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(atanh, std::atanh);
    PROXY_DECL(pythonic::math, atanh);
  }
}

#endif
