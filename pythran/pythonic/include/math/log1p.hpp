#ifndef PYTHONIC_INCLUDE_MATH_LOG1P_HPP
#define PYTHONIC_INCLUDE_MATH_LOG1P_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(log1p, std::log1p);
  }
}

#endif
