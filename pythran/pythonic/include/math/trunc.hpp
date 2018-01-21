#ifndef PYTHONIC_INCLUDE_MATH_TRUNC_HPP
#define PYTHONIC_INCLUDE_MATH_TRUNC_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  DECLARE_FUNCTOR_2(trunc, std::trunc);
}
PYTHONIC_NS_END

#endif
