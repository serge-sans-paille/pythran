#ifndef PYTHONIC_MATH_HYPOT_HPP
#define PYTHONIC_MATH_HYPOT_HPP

#include "pythonic/include/math/hypot.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(hypot, std::hypot);
  }
}

#endif
