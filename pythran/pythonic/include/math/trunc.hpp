#ifndef PYTHONIC_INCLUDE_MATH_TRUNC_HPP
#define PYTHONIC_INCLUDE_MATH_TRUNC_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(trunc, std::trunc);
    PROXY_DECL(pythonic::math, trunc);
  }
}

#endif
