#ifndef PYTHONIC_INCLUDE_NUMPY_SORT_HPP
#define PYTHONIC_INCLUDE_NUMPY_SORT_HPP

#include <algorithm>

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN
namespace numpy
{

  template <class T, size_t N>
  types::ndarray<T, N> sort(types::ndarray<T, N> const &expr, long axis = -1);

  NUMPY_EXPR_TO_NDARRAY0_DECL(sort);
  DECLARE_FUNCTOR(pythonic::numpy, sort);
}
PYTHONIC_NS_END

#endif
