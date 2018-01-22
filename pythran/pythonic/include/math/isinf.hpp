#ifndef PYTHONIC_INCLUDE_MATH_ISINF_HPP
#define PYTHONIC_INCLUDE_MATH_ISINF_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  DECLARE_FUNCTOR_2(isinf, std::isinf);
}
PYTHONIC_NS_END

#endif
