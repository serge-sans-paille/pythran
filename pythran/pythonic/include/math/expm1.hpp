#ifndef PYTHONIC_INCLUDE_MATH_EXPM1_HPP
#define PYTHONIC_INCLUDE_MATH_EXPM1_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(expm1, std::expm1);
  }
}

#endif
