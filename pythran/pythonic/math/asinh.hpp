#ifndef PYTHONIC_MATH_ASINH_HPP
#define PYTHONIC_MATH_ASINH_HPP

#include "pythonic/include/math/asinh.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(asinh, std::asinh);
  }
}

#endif
