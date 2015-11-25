#ifndef PYTHONIC_INCLUDE_MATH_TAN_HPP
#define PYTHONIC_INCLUDE_MATH_TAN_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(tan, std::tan);
  }
}

#endif
