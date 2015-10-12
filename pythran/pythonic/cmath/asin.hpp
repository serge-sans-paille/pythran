#ifndef PYTHONIC_CMATH_ASIN_HPP
#define PYTHONIC_CMATH_ASIN_HPP

#include "pythonic/include/cmath/asin.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS(asin, std::asin);
    PROXY_IMPL(pythonic::cmath, asin);
  }
}

#endif
