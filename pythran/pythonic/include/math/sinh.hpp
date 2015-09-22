#ifndef PYTHONIC_INCLUDE_MATH_SINH_HPP
#define PYTHONIC_INCLUDE_MATH_SINH_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(sinh, std::sinh);
    PROXY_DECL(pythonic::math, sinh);
  }
}

#endif
