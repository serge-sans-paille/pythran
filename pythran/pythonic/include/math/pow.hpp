#ifndef PYTHONIC_INCLUDE_MATH_POW_HPP
#define PYTHONIC_INCLUDE_MATH_POW_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(pow, std::pow);
  }
}

#endif
