#ifndef PYTHONIC_CMATH_LOG_HPP
#define PYTHONIC_CMATH_LOG_HPP

#include "pythonic/include/cmath/log.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {

    ALIAS(log, std::log);

    double log(double x, double base)
    {
      return log(x) / log(base);
    }

    PROXY_IMPL(pythonic::cmath, log);
  }
}

#endif
