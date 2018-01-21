#ifndef PYTHONIC_CMATH_ASIN_HPP
#define PYTHONIC_CMATH_ASIN_HPP

#include "pythonic/include/cmath/asin.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

PYTHONIC_NS_BEGIN

namespace cmath
{
  DEFINE_FUNCTOR_2(asin, std::asin);
}
PYTHONIC_NS_END

#endif
