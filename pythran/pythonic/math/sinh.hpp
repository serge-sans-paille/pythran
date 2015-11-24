#ifndef PYTHONIC_MATH_SINH_HPP
#define PYTHONIC_MATH_SINH_HPP

#include "pythonic/include/math/sinh.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(sinh, std::sinh);
  }
}

#endif
