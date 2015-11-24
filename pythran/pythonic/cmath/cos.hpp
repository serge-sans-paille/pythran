#ifndef PYTHONIC_CMATH_COS_HPP
#define PYTHONIC_CMATH_COS_HPP

#include "pythonic/include/cmath/cos.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/complex.hpp"

#include <cmath>

namespace pythonic
{

  namespace cmath
  {
    template <class T>
    std::complex<T> cos(std::complex<T> const &v)
    {
      return std::cos(v);
    }

    template <class T>
    std::complex<T> cos(T const &v)
    {
      return std::cos(v);
    }

    DEFINE_FUNCTOR(pythonic::cmath, cos);
  }
}

#endif
