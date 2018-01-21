#ifndef PYTHONIC_CMATH_TAN_HPP
#define PYTHONIC_CMATH_TAN_HPP

#include "pythonic/include/cmath/tan.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

PYTHONIC_NS_BEGIN

namespace cmath
{
  DEFINE_FUNCTOR_2(tan, std::tan);
}
PYTHONIC_NS_END

#endif
