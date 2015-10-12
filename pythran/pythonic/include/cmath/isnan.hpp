#ifndef PYTHONIC_INCLUDE_CMATH_ISNAN_HPP
#define PYTHONIC_INCLUDE_CMATH_ISNAN_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS_DECL(isnan, std::isnan);
    PROXY_DECL(pythonic::cmath, isnan);
  }
}

#endif
