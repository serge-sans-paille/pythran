#ifndef PYTHONIC_MATH_ATAN_HPP
#define PYTHONIC_MATH_ATAN_HPP

#include "pythonic/include/math/atan.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  DEFINE_FUNCTOR_2(atan, std::atan);
}
PYTHONIC_NS_END

#endif
