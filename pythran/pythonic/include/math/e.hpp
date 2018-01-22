#ifndef PYTHONIC_INCLUDE_MATH_E_HPP
#define PYTHONIC_INCLUDE_MATH_E_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  double constexpr e = std::exp(1);
}
PYTHONIC_NS_END

#endif
