#ifndef PYTHONIC_MATH_EXP_HPP
#define PYTHONIC_MATH_EXP_HPP

#include "pythonic/include/math/exp.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(exp, std::exp);
  }
}

#endif
