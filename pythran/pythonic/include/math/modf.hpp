#ifndef PYTHONIC_INCLUDE_MATH_MODF_HPP
#define PYTHONIC_INCLUDE_MATH_MODF_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/tuple.hpp"

#include <cmath>

namespace pythonic
{

  namespace math
  {
    std::tuple<double, double> modf(double x);
    DECLARE_FUNCTOR(pythonic::math, modf);
  }
}

#endif
