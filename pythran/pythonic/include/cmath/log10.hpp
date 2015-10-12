#ifndef PYTHONIC_INCLUDE_CMATH_LOG10_HPP
#define PYTHONIC_INCLUDE_CMATH_LOG10_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS_DECL(log10, std::log10);
    PROXY_DECL(pythonic::cmath, log10);
  }
}

#endif
