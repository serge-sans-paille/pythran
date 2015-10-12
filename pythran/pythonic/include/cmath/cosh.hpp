#ifndef PYTHONIC_INCLUDE_CMATH_COSH_HPP
#define PYTHONIC_INCLUDE_CMATH_COSH_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS_DECL(cosh, std::cosh);
    PROXY_DECL(pythonic::cmath, cosh);
  }
}

#endif
