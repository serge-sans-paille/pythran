#ifndef PYTHONIC_INCLUDE_MATH_TANH_HPP
#define PYTHONIC_INCLUDE_MATH_TANH_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(tanh, std::tanh);
    PROXY_DECL(pythonic::math, tanh);
  }
}

#endif
