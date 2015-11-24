#ifndef PYTHONIC_INCLUDE_MATH_SIN_HPP
#define PYTHONIC_INCLUDE_MATH_SIN_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(sin, std::sin);
  }
}

#endif
