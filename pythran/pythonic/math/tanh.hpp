#ifndef PYTHONIC_MATH_TANH_HPP
#define PYTHONIC_MATH_TANH_HPP

#include "pythonic/include/math/tanh.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(tanh, std::tanh);
  }
}

#endif
