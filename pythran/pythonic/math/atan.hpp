#ifndef PYTHONIC_MATH_ATAN_HPP
#define PYTHONIC_MATH_ATAN_HPP

#include "pythonic/include/math/atan.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(atan, std::atan);
  }
}

#endif
