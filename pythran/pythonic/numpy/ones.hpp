#ifndef PYTHONIC_NUMPY_ONES_HPP
#define PYTHONIC_NUMPY_ONES_HPP

#include "pythonic/include/numpy/ones.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  template <class pS, class dtype>
  types::ndarray<typename dtype::type, pS> ones(pS const &shape, dtype d)
  {
    return {shape, typename dtype::type(1)};
  }

  template <class dtype>
  types::ndarray<typename dtype::type, types::pshape<long>> ones(long size,
                                                                 dtype d)
  {
    return ones(types::pshape<long>(size), d);
  }

  DEFINE_FUNCTOR(pythonic::numpy, ones);
}
PYTHONIC_NS_END

#endif
