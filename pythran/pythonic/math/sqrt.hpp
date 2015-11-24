#ifndef PYTHONIC_MATH_SQRT_HPP
#define PYTHONIC_MATH_SQRT_HPP

#include "pythonic/include/math/sqrt.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(sqrt, std::sqrt);
  }
}

#endif
