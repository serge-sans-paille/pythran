#ifndef PYTHONIC_INCLUDE_MATH_LOG_HPP
#define PYTHONIC_INCLUDE_MATH_LOG_HPP

#include "pythonic/include/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    using std::log;
    double log(double x, double base);
    DECLARE_FUNCTOR(pythonic::math, log);
  }
}

#endif
