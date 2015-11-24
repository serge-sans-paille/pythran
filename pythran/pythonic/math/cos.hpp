#ifndef PYTHONIC_MATH_COS_HPP
#define PYTHONIC_MATH_COS_HPP

#include "pythonic/include/math/cos.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(cos, std::cos);
  }
}

#endif
