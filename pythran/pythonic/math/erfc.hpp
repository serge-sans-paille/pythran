#ifndef PYTHONIC_MATH_ERFC_HPP
#define PYTHONIC_MATH_ERFC_HPP

#include "pythonic/include/math/erfc.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(erfc, std::erfc);
  }
}

#endif
