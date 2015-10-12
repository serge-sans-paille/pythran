#ifndef PYTHONIC_INCLUDE_CMATH_TANH_HPP
#define PYTHONIC_INCLUDE_CMATH_TANH_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS_DECL(tanh, std::tanh);
    PROXY_DECL(pythonic::cmath, tanh);
  }
}

#endif
