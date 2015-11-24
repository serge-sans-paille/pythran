#ifndef PYTHONIC_INCLUDE_MATH_ISINF_HPP
#define PYTHONIC_INCLUDE_MATH_ISINF_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(isinf, std::isinf);
  }
}

#endif
