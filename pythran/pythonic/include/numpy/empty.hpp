#ifndef PYTHONIC_INCLUDE_NUMPY_EMPTY_HPP
#define PYTHONIC_INCLUDE_NUMPY_EMPTY_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/float64.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class pS, class dtype = functor::float64>
  types::ndarray<typename dtype::type, pS> empty(pS const &shape,
                                                 dtype d = dtype());

  template <class dtype = functor::float64>
  types::ndarray<typename dtype::type, types::pshape<long>>
  empty(long size, dtype d = dtype());

  DECLARE_FUNCTOR(pythonic::numpy, empty);
}
PYTHONIC_NS_END

#endif
