#ifndef PYTHONIC_INCLUDE_CMATH_COS_HPP
#define PYTHONIC_INCLUDE_CMATH_COS_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    template <class T>
    std::complex<T> cos(std::complex<T> const &v);
    template <class T>
    std::complex<T> cos(T const &v);

    DECLARE_FUNCTOR(pythonic::cmath, cos);
  }
}

#endif
