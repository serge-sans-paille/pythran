#ifndef PYTHONIC_MATH_ISNAN_HPP
#define PYTHONIC_MATH_ISNAN_HPP

#include "pythonic/include/math/isnan.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(isnan, std::isnan);
  }
}

#endif
