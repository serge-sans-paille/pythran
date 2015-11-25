#ifndef PYTHONIC_INCLUDE_CMATH_LOG_HPP
#define PYTHONIC_INCLUDE_CMATH_LOG_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    using std::log;
    double log(double x, double base);
    DECLARE_FUNCTOR(pythonic::cmath, log);
  }
}

#endif
