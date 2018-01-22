#ifndef PYTHONIC_INCLUDE_MATH_CEIL_HPP
#define PYTHONIC_INCLUDE_MATH_CEIL_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  DECLARE_FUNCTOR_2(ceil, std::ceil);
}
PYTHONIC_NS_END

#endif
