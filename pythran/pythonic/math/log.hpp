#ifndef PYTHONIC_MATH_LOG_HPP
#define PYTHONIC_MATH_LOG_HPP

#include "pythonic/include/math/log.hpp"

#include "pythonic/utils/functor.hpp"
#include <cmath>

PYTHONIC_NS_BEGIN

namespace math
{
  using std::log;

  double log(double x, double base)
  {
    return log(x) / log(base);
  }

  DEFINE_FUNCTOR(pythonic::math, log);
}
PYTHONIC_NS_END

#endif
