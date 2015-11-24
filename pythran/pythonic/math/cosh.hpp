#ifndef PYTHONIC_MATH_COSH_HPP
#define PYTHONIC_MATH_COSH_HPP

#include "pythonic/include/math/cosh.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(cosh, std::cosh);
  }
}

#endif
