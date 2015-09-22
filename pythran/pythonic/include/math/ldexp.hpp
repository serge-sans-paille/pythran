#ifndef PYTHONIC_INCLUDE_MATH_LDEXP_HPP
#define PYTHONIC_INCLUDE_MATH_LDEXP_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(ldexp, std::ldexp);
    PROXY_DECL(pythonic::math, ldexp);
  }
}

#endif
