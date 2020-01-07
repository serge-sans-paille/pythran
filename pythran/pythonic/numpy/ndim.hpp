#ifndef PYTHONIC_NUMPY_NDIM_HPP
#define PYTHONIC_NUMPY_NDIM_HPP

#include "pythonic/include/numpy/ndim.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  template <class E>
  auto ndim(E const &e) -> decltype(builtins::getattr(types::attr::NDIM{}, e))
  {
    return builtins::getattr(types::attr::NDIM{}, e);
  }
}
PYTHONIC_NS_END

#endif
