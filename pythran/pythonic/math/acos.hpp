#ifndef PYTHONIC_MATH_ACOS_HPP
#define PYTHONIC_MATH_ACOS_HPP

#include "pythonic/include/math/acos.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(acos, std::acos);
  }
}

#endif
