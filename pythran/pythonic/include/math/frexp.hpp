#ifndef PYTHONIC_INCLUDE_MATH_FREXP_HPP
#define PYTHONIC_INCLUDE_MATH_FREXP_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/tuple.hpp"

#include <cmath>

namespace pythonic
{

  namespace math
  {
    std::tuple<double, long> frexp(double x);
    DECLARE_FUNCTOR(pythonic::math, frexp);
  }
}

#endif
