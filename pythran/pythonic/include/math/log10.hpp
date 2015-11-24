#ifndef PYTHONIC_INCLUDE_MATH_LOG10_HPP
#define PYTHONIC_INCLUDE_MATH_LOG10_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(log10, std::log10);
  }
}

#endif
