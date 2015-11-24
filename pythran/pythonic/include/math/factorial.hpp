#ifndef PYTHONIC_INCLUDE_MATH_FACTORIAL_HPP
#define PYTHONIC_INCLUDE_MATH_FACTORIAL_HPP

#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace math
  {

    template <class T>
    T factorial(T x);

    DECLARE_FUNCTOR(pythonic::math, factorial);
  }
}

#endif
