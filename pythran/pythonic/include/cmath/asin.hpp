#ifndef PYTHONIC_INCLUDE_CMATH_ASIN_HPP
#define PYTHONIC_INCLUDE_CMATH_ASIN_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS_DECL(asin, std::asin);
    PROXY_DECL(pythonic::cmath, asin);
  }
}

#endif
