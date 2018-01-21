#ifndef PYTHONIC_MATH_FLOOR_HPP
#define PYTHONIC_MATH_FLOOR_HPP

#include "pythonic/include/math/floor.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  DEFINE_FUNCTOR_2(floor, std::floor);
}
PYTHONIC_NS_END

#endif
