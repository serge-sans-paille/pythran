#ifndef PYTHONIC_MATH_TAN_HPP
#define PYTHONIC_MATH_TAN_HPP

#include "pythonic/include/math/tan.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(tan, std::tan);
  }
}

#endif
