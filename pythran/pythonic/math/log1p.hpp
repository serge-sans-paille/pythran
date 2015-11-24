#ifndef PYTHONIC_MATH_LOG1P_HPP
#define PYTHONIC_MATH_LOG1P_HPP

#include "pythonic/include/math/log1p.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(log1p, std::log1p);
  }
}

#endif
