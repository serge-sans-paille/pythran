#ifndef PYTHONIC_MATH_ATANH_HPP
#define PYTHONIC_MATH_ATANH_HPP

#include "pythonic/include/math/atanh.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(atanh, std::atanh);
  }
}

#endif
