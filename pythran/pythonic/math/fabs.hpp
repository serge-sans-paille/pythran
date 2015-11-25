#ifndef PYTHONIC_MATH_FABS_HPP
#define PYTHONIC_MATH_FABS_HPP

#include "pythonic/include/math/fabs.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(fabs, std::fabs);
  }
}

#endif
