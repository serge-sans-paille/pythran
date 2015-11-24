#ifndef PYTHONIC_INCLUDE_MATH_CEIL_HPP
#define PYTHONIC_INCLUDE_MATH_CEIL_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(ceil, std::ceil);
  }
}

#endif
