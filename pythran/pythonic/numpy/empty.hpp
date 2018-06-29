#ifndef PYTHONIC_NUMPY_EMPTY_HPP
#define PYTHONIC_NUMPY_EMPTY_HPP

#include "pythonic/include/numpy/empty.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class pS, class dtype>
  types::ndarray<typename dtype::type, pS> empty(pS const &shape, dtype)
  {
    return {shape, __builtin__::None};
  }

  template <class dtype>
  types::ndarray<typename dtype::type, types::pshape<long>> empty(long size,
                                                                  dtype d)
  {
    return empty(types::make_tuple(size), d);
  }

  DEFINE_FUNCTOR(pythonic::numpy, empty);
}
PYTHONIC_NS_END

#endif
