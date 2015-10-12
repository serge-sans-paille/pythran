#ifndef PYTHONIC_INCLUDE_CMATH_ATANH_HPP
#define PYTHONIC_INCLUDE_CMATH_ATANH_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS_DECL(atanh, std::atanh);
    PROXY_DECL(pythonic::cmath, atanh);
  }
}

#endif
