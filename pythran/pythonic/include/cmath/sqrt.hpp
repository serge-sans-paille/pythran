#ifndef PYTHONIC_INCLUDE_CMATH_SQRT_HPP
#define PYTHONIC_INCLUDE_CMATH_SQRT_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS_DECL(sqrt, std::sqrt);
    PROXY_DECL(pythonic::cmath, sqrt);
  }
}

#endif
