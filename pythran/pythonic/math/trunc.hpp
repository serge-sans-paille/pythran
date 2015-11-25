#ifndef PYTHONIC_MATH_TRUNC_HPP
#define PYTHONIC_MATH_TRUNC_HPP

#include "pythonic/include/math/trunc.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(trunc, std::trunc);
  }
}

#endif
