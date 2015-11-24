#ifndef PYTHONIC_INCLUDE_MATH_FABS_HPP
#define PYTHONIC_INCLUDE_MATH_FABS_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(fabs, std::fabs);
  }
}

#endif
