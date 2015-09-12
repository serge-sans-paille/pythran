#ifndef PYTHONIC_INCLUDE_MATH_ERFC_HPP
#define PYTHONIC_INCLUDE_MATH_ERFC_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(erfc, std::erfc);
    PROXY_DECL(pythonic::math, erfc);
  }
}

#endif
