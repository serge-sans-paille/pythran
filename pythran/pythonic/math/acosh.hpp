#ifndef PYTHONIC_MATH_ACOSH_HPP
#define PYTHONIC_MATH_ACOSH_HPP

#include "pythonic/include/math/acosh.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(acosh, std::acosh);
  }
}

#endif
