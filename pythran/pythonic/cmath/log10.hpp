#ifndef PYTHONIC_CMATH_LOG10_HPP
#define PYTHONIC_CMATH_LOG10_HPP

#include "pythonic/include/cmath/log10.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

PYTHONIC_NS_BEGIN

namespace cmath
{
  DEFINE_FUNCTOR_2(log10, std::log10);
}
PYTHONIC_NS_END

#endif
