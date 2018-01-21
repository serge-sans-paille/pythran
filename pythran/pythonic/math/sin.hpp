#ifndef PYTHONIC_MATH_SIN_HPP
#define PYTHONIC_MATH_SIN_HPP

#include "pythonic/include/math/sin.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  DEFINE_FUNCTOR_2(sin, std::sin);
}
PYTHONIC_NS_END

#endif
