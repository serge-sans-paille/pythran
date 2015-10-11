#ifndef PYTHONIC_INCLUDE_CMATH_TAN_HPP
#define PYTHONIC_INCLUDE_CMATH_TAN_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS_DECL(tan, std::tan);
    PROXY_DECL(pythonic::cmath, tan);
  }
}

#endif
