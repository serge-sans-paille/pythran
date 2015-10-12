#ifndef PYTHONIC_CMATH_ISNAN_HPP
#define PYTHONIC_CMATH_ISNAN_HPP

#include "pythonic/include/cmath/isnan.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS(isnan, std::isnan);
    PROXY_IMPL(pythonic::cmath, isnan);
  }
}

#endif
