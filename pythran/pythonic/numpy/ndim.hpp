#ifndef PYTHONIC_NUMPY_NDIM_HPP
#define PYTHONIC_NUMPY_NDIM_HPP

#include "pythonic/include/numpy/ndim.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  template <class E>
  auto ndim(E const &e) -> decltype(__builtin__::getattr<types::attr::NDIM>(e))
  {
    return __builtin__::getattr<types::attr::NDIM>(e);
  }

  DEFINE_FUNCTOR(pythonic::numpy, ndim)
}
PYTHONIC_NS_END

#endif
