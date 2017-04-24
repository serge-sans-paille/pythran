#ifndef PYTHONIC_INCLUDE_NUMPY_FLATNONZERO_HPP
#define PYTHONIC_INCLUDE_NUMPY_FLATNONZERO_HPP

#include "pythonic/include/numpy/asarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    types::ndarray<long, 1> flatnonzero(E const &expr);

    DECLARE_FUNCTOR(pythonic::numpy, flatnonzero);
  }
}

#endif
