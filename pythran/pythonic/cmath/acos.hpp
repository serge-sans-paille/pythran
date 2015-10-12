#ifndef PYTHONIC_CMATH_ACOS_HPP
#define PYTHONIC_CMATH_ACOS_HPP

#include "pythonic/include/cmath/acos.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS(acos, std::acos);
    PROXY_IMPL(pythonic::cmath, acos);
  }
}

#endif
