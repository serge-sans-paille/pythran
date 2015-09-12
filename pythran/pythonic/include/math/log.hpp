#ifndef PYTHONIC_INCLUDE_MATH_LOG_HPP
#define PYTHONIC_INCLUDE_MATH_LOG_HPP

#include "pythonic/include/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    ALIAS_DECL(log, std::log);
    double log(double x, double base);
    PROXY_DECL(pythonic::math, log);
  }
}

#endif
