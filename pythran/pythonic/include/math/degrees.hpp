#ifndef PYTHONIC_INCLUDE_MATH_DEGREES_HPP
#define PYTHONIC_INCLUDE_MATH_DEGREES_HPP

#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace math
  {

    template <class T>
    double degrees(T x);

    PROXY_DECL(pythonic::math, degrees);
  }
}

#endif
