#ifndef PYTHONIC_CMATH_TANH_HPP
#define PYTHONIC_CMATH_TANH_HPP

#include "pythonic/include/cmath/tanh.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    ALIAS(tanh, std::tanh);
    PROXY_IMPL(pythonic::cmath, tanh);
  }
}

#endif
