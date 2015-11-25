#ifndef PYTHONIC_MATH_FREXP_HPP
#define PYTHONIC_MATH_FREXP_HPP

#include "pythonic/include/math/frexp.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/tuple.hpp"

#include <cmath>

namespace pythonic
{

  namespace math
  {
    std::tuple<double, long> frexp(double x)
    {
      int exp;
      double sig = std::frexp(x, &exp);
      return std::tuple<double, long>(sig, exp);
    }
    DEFINE_FUNCTOR(pythonic::math, frexp);
  }
}

#endif
