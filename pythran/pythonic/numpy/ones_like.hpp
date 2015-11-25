#ifndef PYTHONIC_NUMPY_ONESLIKE_HPP
#define PYTHONIC_NUMPY_ONESLIKE_HPP

#include "pythonic/include/numpy/ones_like.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/numpy/ones.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    auto ones_like(E const &expr) -> decltype(ones(expr.shape()))
    {
      return ones(expr.shape());
    }

    DEFINE_FUNCTOR(pythonic::numpy, ones_like)
  }
}

#endif
