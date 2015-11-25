#ifndef PYTHONIC_MATH_COPYSIGN_HPP
#define PYTHONIC_MATH_COPYSIGN_HPP

#include "pythonic/include/math/copysign.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(copysign, std::copysign);
  }
}

#endif
