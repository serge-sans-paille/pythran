#ifndef PYTHONIC_INCLUDE_NUMPY_ONESLIKE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ONESLIKE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/ones.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    auto ones_like(E const &expr) -> decltype(ones(expr.shape()));

    DECLARE_FUNCTOR(pythonic::numpy, ones_like)
  }
}

#endif
