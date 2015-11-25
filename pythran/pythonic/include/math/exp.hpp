#ifndef PYTHONIC_INCLUDE_MATH_EXP_HPP
#define PYTHONIC_INCLUDE_MATH_EXP_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(exp, std::exp);
  }
}

#endif
