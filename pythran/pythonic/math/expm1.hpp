#ifndef PYTHONIC_MATH_EXPM1_HPP
#define PYTHONIC_MATH_EXPM1_HPP

#include "pythonic/include/math/expm1.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(expm1, std::expm1);
  }
}

#endif
