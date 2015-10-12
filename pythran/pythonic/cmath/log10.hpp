#ifndef PYTHONIC_CMATH_LOG10_HPP
#define PYTHONIC_CMATH_LOG10_HPP

#include "pythonic/include/cmath/log10.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS(log10, std::log10);
    PROXY_IMPL(pythonic::cmath, log10);
  }
}

#endif
