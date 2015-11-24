#ifndef PYTHONIC_INCLUDE_MATH_SQRT_HPP
#define PYTHONIC_INCLUDE_MATH_SQRT_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(sqrt, std::sqrt);
  }
}

#endif
