#ifndef PYTHONIC_MATH_ASIN_HPP
#define PYTHONIC_MATH_ASIN_HPP

#include "pythonic/include/math/asin.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  DEFINE_FUNCTOR_2(asin, std::asin);
}
PYTHONIC_NS_END

#endif
