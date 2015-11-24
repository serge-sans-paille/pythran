#ifndef PYTHONIC_INCLUDE_MATH_ISNAN_HPP
#define PYTHONIC_INCLUDE_MATH_ISNAN_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(isnan, std::isnan);
  }
}

#endif
