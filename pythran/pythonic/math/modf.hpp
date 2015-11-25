#ifndef PYTHONIC_MATH_MODF_HPP
#define PYTHONIC_MATH_MODF_HPP

#include "pythonic/include/math/modf.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/tuple.hpp"

#include <cmath>

namespace pythonic
{

  namespace math
  {

    std::tuple<double, double> modf(double x)
    {
      double i;
      double frac = std::modf(x, &i);
      return std::make_tuple(frac, i);
    }

    DEFINE_FUNCTOR(pythonic::math, modf);
  }
}

#endif
