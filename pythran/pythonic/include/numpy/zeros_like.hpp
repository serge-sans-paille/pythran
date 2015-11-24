#ifndef PYTHONIC_INCLUDE_NUMPY_ZEROSLIKE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ZEROSLIKE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/zeros.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class E>
    auto zeros_like(E const &expr) -> decltype(zeros(expr.shape()));

    DECLARE_FUNCTOR(pythonic::numpy, zeros_like)
  }
}

#endif
