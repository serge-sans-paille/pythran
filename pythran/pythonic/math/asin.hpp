#ifndef PYTHONIC_MATH_ASIN_HPP
#define PYTHONIC_MATH_ASIN_HPP

#include "pythonic/include/math/asin.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    DEFINE_FUNCTOR_2(asin, std::asin);
  }
}

#endif
