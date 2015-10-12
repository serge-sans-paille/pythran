#ifndef PYTHONIC_CMATH_SINH_HPP
#define PYTHONIC_CMATH_SINH_HPP

#include "pythonic/include/cmath/sinh.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS(sinh, std::sinh);
    PROXY_IMPL(pythonic::cmath, sinh);
  }
}

#endif
