#ifndef PYTHONIC_INCLUDE_MATH_ERFC_HPP
#define PYTHONIC_INCLUDE_MATH_ERFC_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DECLARE_FUNCTOR_2(erfc, std::erfc);
  }
}

#endif
