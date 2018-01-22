#ifndef PYTHONIC_MATH_LOG10_HPP
#define PYTHONIC_MATH_LOG10_HPP

#include "pythonic/include/math/log10.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  DEFINE_FUNCTOR_2(log10, std::log10);
}
PYTHONIC_NS_END

#endif
