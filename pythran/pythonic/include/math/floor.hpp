#ifndef PYTHONIC_INCLUDE_MATH_FLOOR_HPP
#define PYTHONIC_INCLUDE_MATH_FLOOR_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(floor, std::floor);
  }
}

#endif
