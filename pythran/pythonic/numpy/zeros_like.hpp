#ifndef PYTHONIC_NUMPY_ZEROSLIKE_HPP
#define PYTHONIC_NUMPY_ZEROSLIKE_HPP

#include "pythonic/include/numpy/zeros_like.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/numpy/zeros.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E>
    auto zeros_like(E const &expr) -> decltype(zeros(expr.shape()))
    {
      return zeros(expr.shape());
    }

    DEFINE_FUNCTOR(pythonic::numpy, zeros_like)
  }
}

#endif
