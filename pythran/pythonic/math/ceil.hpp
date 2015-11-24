#ifndef PYTHONIC_MATH_CEIL_HPP
#define PYTHONIC_MATH_CEIL_HPP

#include "pythonic/include/math/ceil.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(ceil, std::ceil);
  }
}

#endif
