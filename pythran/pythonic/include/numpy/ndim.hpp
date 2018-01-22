#ifndef PYTHONIC_INCLUDE_NUMPY_NDIM_HPP
#define PYTHONIC_INCLUDE_NUMPY_NDIM_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  template <class E>
  auto ndim(E const &e) -> decltype(__builtin__::getattr<types::attr::NDIM>(e));

  DECLARE_FUNCTOR(pythonic::numpy, ndim)
}
PYTHONIC_NS_END

#endif
