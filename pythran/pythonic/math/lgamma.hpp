#ifndef PYTHONIC_MATH_LGAMMA_HPP
#define PYTHONIC_MATH_LGAMMA_HPP

#include "pythonic/include/math/lgamma.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  DEFINE_FUNCTOR_2(lgamma, std::lgamma);
}
PYTHONIC_NS_END

#endif
