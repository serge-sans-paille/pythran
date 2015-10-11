#ifndef PYTHONIC_CMATH_ATAN_HPP
#define PYTHONIC_CMATH_ATAN_HPP

#include "pythonic/include/cmath/atan.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS(atan, std::atan);
    PROXY_IMPL(pythonic::cmath, atan);
  }
}

#endif
