#ifndef PYTHONIC_MATH_LGAMMA_HPP
#define PYTHONIC_MATH_LGAMMA_HPP

#include "pythonic/include/math/lgamma.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(lgamma, std::lgamma);
  }
}

#endif
