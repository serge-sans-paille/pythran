#ifndef PYTHONIC_CMATH_LOG_HPP
#define PYTHONIC_CMATH_LOG_HPP

#include "pythonic/include/cmath/log.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    using std::log;
    double log(double x, double base)
    {
      return log(x) / log(base);
    }

    DEFINE_FUNCTOR(pythonic::cmath, log);
  }
}

#endif
