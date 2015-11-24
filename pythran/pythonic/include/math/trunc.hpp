#ifndef PYTHONIC_INCLUDE_MATH_TRUNC_HPP
#define PYTHONIC_INCLUDE_MATH_TRUNC_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(trunc, std::trunc);
  }
}

#endif
