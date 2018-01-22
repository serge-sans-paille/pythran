#ifndef PYTHONIC_CMATH_EXP_HPP
#define PYTHONIC_CMATH_EXP_HPP

#include "pythonic/include/cmath/exp.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

PYTHONIC_NS_BEGIN

namespace cmath
{
  DEFINE_FUNCTOR_2(exp, std::exp);
}
PYTHONIC_NS_END

#endif
