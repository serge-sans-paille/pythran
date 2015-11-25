#ifndef PYTHONIC_INCLUDE_MATH_ATAN2_HPP
#define PYTHONIC_INCLUDE_MATH_ATAN2_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(atan2, std::atan2);
  }
}

#endif
