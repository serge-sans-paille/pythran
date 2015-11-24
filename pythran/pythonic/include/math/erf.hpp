#ifndef PYTHONIC_INCLUDE_MATH_ERF_HPP
#define PYTHONIC_INCLUDE_MATH_ERF_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(erf, std::erf);
  }
}

#endif
