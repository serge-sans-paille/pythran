#ifndef PYTHONIC_MATH_SINH_HPP
#define PYTHONIC_MATH_SINH_HPP

#include "pythonic/include/math/sinh.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  DEFINE_FUNCTOR_2(sinh, std::sinh);
}
PYTHONIC_NS_END

#endif
