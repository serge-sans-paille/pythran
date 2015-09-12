#ifndef PYTHONIC_INCLUDE_MATH_ISINF_HPP
#define PYTHONIC_INCLUDE_MATH_ISINF_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(isinf, std::isinf);
    PROXY_DECL(pythonic::math, isinf);
  }
}

#endif
