#ifndef PYTHONIC_INCLUDE_CMATH_LOG_HPP
#define PYTHONIC_INCLUDE_CMATH_LOG_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS_DECL(log, std::log);
    double log(double x, double base);
    PROXY_DECL(pythonic::cmath, log);
  }
}

#endif
