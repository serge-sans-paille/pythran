#ifndef PYTHONIC_INCLUDE_MATH_TANH_HPP
#define PYTHONIC_INCLUDE_MATH_TANH_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(tanh, std::tanh);
  }
}

#endif
