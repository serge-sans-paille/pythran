#ifndef PYTHONIC_INCLUDE_MATH_PI_HPP
#define PYTHONIC_INCLUDE_MATH_PI_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{

  double const pi = std::atan(1) * 4;
}
PYTHONIC_NS_END

#endif
