#ifndef PYTHONIC_MATH_SQRT_HPP
#define PYTHONIC_MATH_SQRT_HPP

#include "pythonic/include/math/sqrt.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  DEFINE_FUNCTOR_2(sqrt, std::sqrt);
}
PYTHONIC_NS_END

#endif
