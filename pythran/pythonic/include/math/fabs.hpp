#ifndef PYTHONIC_INCLUDE_MATH_FABS_HPP
#define PYTHONIC_INCLUDE_MATH_FABS_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(fabs, std::fabs);
    PROXY_DECL(pythonic::math, fabs);
  }
}

#endif
