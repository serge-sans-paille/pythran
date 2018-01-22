#ifndef PYTHONIC_INCLUDE_NUMPY_RAVEL_HPP
#define PYTHONIC_INCLUDE_NUMPY_RAVEL_HPP

#include "pythonic/include/numpy/reshape.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T, size_t N>
  types::ndarray<T, 1> ravel(types::ndarray<T, N> const &expr);

  NUMPY_EXPR_TO_NDARRAY0_DECL(ravel);
  DECLARE_FUNCTOR(pythonic::numpy, ravel);
}
PYTHONIC_NS_END

#endif
