#ifndef PYTHONIC_CMATH_ASINH_HPP
#define PYTHONIC_CMATH_ASINH_HPP

#include "pythonic/include/cmath/asinh.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

PYTHONIC_NS_BEGIN

namespace cmath
{
  DEFINE_FUNCTOR_2(asinh, std::asinh);
}
PYTHONIC_NS_END

#endif
