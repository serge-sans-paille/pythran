#ifndef PYTHONIC_CMATH_ASINH_HPP
#define PYTHONIC_CMATH_ASINH_HPP

#include "pythonic/include/cmath/asinh.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS(asinh, std::asinh);
    PROXY_IMPL(pythonic::cmath, asinh);
  }
}

#endif
