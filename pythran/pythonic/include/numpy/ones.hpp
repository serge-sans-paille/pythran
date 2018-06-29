#ifndef PYTHONIC_INCLUDE_NUMPY_ONES_HPP
#define PYTHONIC_INCLUDE_NUMPY_ONES_HPP

#include "pythonic/include/numpy/float64.hpp"
#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  template <class pS, class dtype = functor::float64>
  types::ndarray<typename dtype::type, pS> ones(pS const &shape,
                                                dtype d = dtype());

  template <class dtype = functor::float64>
  types::ndarray<typename dtype::type, types::pshape<long>>
  ones(long size, dtype d = dtype());

  DECLARE_FUNCTOR(pythonic::numpy, ones);
}
PYTHONIC_NS_END

#endif
