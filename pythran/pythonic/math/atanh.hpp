#ifndef PYTHONIC_MATH_ATANH_HPP
#define PYTHONIC_MATH_ATANH_HPP

#include "pythonic/include/math/atanh.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  DEFINE_FUNCTOR_2(atanh, std::atanh);
}
PYTHONIC_NS_END

#endif
