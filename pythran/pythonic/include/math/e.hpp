#ifndef PYTHONIC_INCLUDE_MATH_E_HPP
#define PYTHONIC_INCLUDE_MATH_E_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    double PYTHONIC_CONSTEXPR e = std::exp(1);
  }
}

#endif
