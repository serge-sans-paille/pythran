#ifndef PYTHONIC_INCLUDE_MATH_ERF_HPP
#define PYTHONIC_INCLUDE_MATH_ERF_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(erf, std::erf);
    PROXY_DECL(pythonic::math, erf);
  }
}

#endif
