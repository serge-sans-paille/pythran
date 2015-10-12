#ifndef PYTHONIC_CMATH_COSH_HPP
#define PYTHONIC_CMATH_COSH_HPP

#include "pythonic/include/cmath/cosh.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS(cosh, std::cosh);
    PROXY_IMPL(pythonic::cmath, cosh);
  }
}

#endif
