#ifndef PYTHONIC_CMATH_SIN_HPP
#define PYTHONIC_CMATH_SIN_HPP

#include "pythonic/include/cmath/sin.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS(sin, std::sin);
    PROXY_IMPL(pythonic::cmath, sin);
  }
}

#endif
