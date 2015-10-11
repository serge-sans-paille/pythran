#ifndef PYTHONIC_CMATH_SQRT_HPP
#define PYTHONIC_CMATH_SQRT_HPP

#include "pythonic/include/cmath/sqrt.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS(sqrt, std::sqrt);
    PROXY_IMPL(pythonic::cmath, sqrt);
  }
}

#endif
