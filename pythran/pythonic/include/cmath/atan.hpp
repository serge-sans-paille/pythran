#ifndef PYTHONIC_INCLUDE_CMATH_ATAN_HPP
#define PYTHONIC_INCLUDE_CMATH_ATAN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/complex.hpp"

#include <cmath>

PYTHONIC_NS_BEGIN

namespace cmath
{
  DECLARE_FUNCTOR_2(atan, std::atan);
}
PYTHONIC_NS_END

#endif
