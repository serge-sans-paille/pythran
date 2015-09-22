#ifndef PYTHONIC_INCLUDE_MATH_EXP_HPP
#define PYTHONIC_INCLUDE_MATH_EXP_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(exp, std::exp);
    PROXY_DECL(pythonic::math, exp);
  }
}

#endif
