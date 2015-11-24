#ifndef PYTHONIC_INCLUDE_CMATH_PI_HPP
#define PYTHONIC_INCLUDE_CMATH_PI_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    double constexpr pi = std::atan(1) * 4;
  }
}

#endif
