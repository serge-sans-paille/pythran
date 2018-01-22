#ifndef PYTHONIC_MATH_ISINF_HPP
#define PYTHONIC_MATH_ISINF_HPP

#include "pythonic/include/math/isinf.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  DEFINE_FUNCTOR_2(isinf, std::isinf);
}
PYTHONIC_NS_END

#endif
