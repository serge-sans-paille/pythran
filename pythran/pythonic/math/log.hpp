#ifndef PYTHONIC_MATH_LOG_HPP
#define PYTHONIC_MATH_LOG_HPP

#include "pythonic/include/math/log.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

namespace pythonic
{

  namespace math
  {
    using std::log;

    double log(double x, double base)
    {
      return log(x) / log(base);
    }

    DEFINE_FUNCTOR(pythonic::math, log);
  }
}

#endif
