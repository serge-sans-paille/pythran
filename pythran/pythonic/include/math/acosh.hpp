#ifndef PYTHONIC_INCLUDE_MATH_ACOSH_HPP
#define PYTHONIC_INCLUDE_MATH_ACOSH_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(acosh, std::acosh);
    PROXY_DECL(pythonic::math, acosh);
  }
}

#endif
