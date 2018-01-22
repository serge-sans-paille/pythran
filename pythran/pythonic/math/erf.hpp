#ifndef PYTHONIC_MATH_ERF_HPP
#define PYTHONIC_MATH_ERF_HPP

#include "pythonic/include/math/erf.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  DEFINE_FUNCTOR_2(erf, std::erf);
}
PYTHONIC_NS_END

#endif
