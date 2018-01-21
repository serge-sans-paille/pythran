#ifndef PYTHONIC_MATH_HYPOT_HPP
#define PYTHONIC_MATH_HYPOT_HPP

#include "pythonic/include/math/hypot.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  DEFINE_FUNCTOR_2(hypot, std::hypot);
}
PYTHONIC_NS_END

#endif
