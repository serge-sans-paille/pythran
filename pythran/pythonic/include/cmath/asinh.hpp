#ifndef PYTHONIC_INCLUDE_CMATH_ASINH_HPP
#define PYTHONIC_INCLUDE_CMATH_ASINH_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS_DECL(asinh, std::asinh);
    PROXY_DECL(pythonic::cmath, asinh);
  }
}

#endif
