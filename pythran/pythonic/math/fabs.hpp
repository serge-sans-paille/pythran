#ifndef PYTHONIC_MATH_FABS_HPP
#define PYTHONIC_MATH_FABS_HPP

#include "pythonic/include/math/fabs.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  DEFINE_FUNCTOR_2(fabs, std::fabs);
}
PYTHONIC_NS_END

#endif
