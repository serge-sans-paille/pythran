#ifndef PYTHONIC_INCLUDE_MATH_FREXP_HPP
#define PYTHONIC_INCLUDE_MATH_FREXP_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/tuple.hpp"

#include <cmath>

namespace pythonic
{

  namespace math
  {
    std::tuple<double, long> frexp(double x);
    PROXY_DECL(pythonic::math, frexp);
  }
}

#endif
