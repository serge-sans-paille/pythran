#ifndef PYTHONIC_NUMPY_ONES_HPP
#define PYTHONIC_NUMPY_ONES_HPP

#include "pythonic/include/numpy/ones.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  template <size_t N, class dtype>
  types::ndarray<typename dtype::type, N>
  ones(types::array<long, N> const &shape, dtype d)
  {
    return {shape, typename dtype::type(1)};
  }

  template <class dtype>
  types::ndarray<typename dtype::type, 1> ones(long size, dtype d)
  {
    return ones(types::make_tuple(size), d);
  }

  DEFINE_FUNCTOR(pythonic::numpy, ones);
}
PYTHONIC_NS_END

#endif
