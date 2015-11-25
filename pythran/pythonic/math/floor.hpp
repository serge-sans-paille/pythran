#ifndef PYTHONIC_MATH_FLOOR_HPP
#define PYTHONIC_MATH_FLOOR_HPP

#include "pythonic/include/math/floor.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(floor, std::floor);
  }
}

#endif
