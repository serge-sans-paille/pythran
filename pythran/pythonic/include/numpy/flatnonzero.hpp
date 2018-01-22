#ifndef PYTHONIC_INCLUDE_NUMPY_FLATNONZERO_HPP
#define PYTHONIC_INCLUDE_NUMPY_FLATNONZERO_HPP

#include "pythonic/include/numpy/asarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class E>
  types::ndarray<long, 1> flatnonzero(E const &expr);

  DECLARE_FUNCTOR(pythonic::numpy, flatnonzero);
}
PYTHONIC_NS_END

#endif
