#ifndef PYTHONIC_CMATH_ISNAN_HPP
#define PYTHONIC_CMATH_ISNAN_HPP

#include "pythonic/include/cmath/isnan.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

PYTHONIC_NS_BEGIN

namespace cmath
{
  DEFINE_FUNCTOR_2(isnan, std::isnan);
}
PYTHONIC_NS_END

#endif
