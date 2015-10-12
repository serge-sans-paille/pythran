#ifndef PYTHONIC_CMATH_TAN_HPP
#define PYTHONIC_CMATH_TAN_HPP

#include "pythonic/include/cmath/tan.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS(tan, std::tan);
    PROXY_IMPL(pythonic::cmath, tan);
  }
}

#endif
