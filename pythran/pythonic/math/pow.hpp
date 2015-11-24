#ifndef PYTHONIC_MATH_POW_HPP
#define PYTHONIC_MATH_POW_HPP

#include "pythonic/include/math/pow.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(pow, std::pow);
  }
}

#endif
