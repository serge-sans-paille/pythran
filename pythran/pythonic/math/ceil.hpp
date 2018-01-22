#ifndef PYTHONIC_MATH_CEIL_HPP
#define PYTHONIC_MATH_CEIL_HPP

#include "pythonic/include/math/ceil.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  DEFINE_FUNCTOR_2(ceil, std::ceil);
}
PYTHONIC_NS_END

#endif
