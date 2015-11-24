#ifndef PYTHONIC_MATH_SIN_HPP
#define PYTHONIC_MATH_SIN_HPP

#include "pythonic/include/math/sin.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(sin, std::sin);
  }
}

#endif
