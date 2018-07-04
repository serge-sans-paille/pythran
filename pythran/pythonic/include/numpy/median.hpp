#ifndef PYTHONIC_INCLUDE_NUMPY_MEDIAN_HPP
#define PYTHONIC_INCLUDE_NUMPY_MEDIAN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/numpy/asarray.hpp"
#include <algorithm>

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T, class pS>
  decltype(std::declval<T>() + 1.) median(types::ndarray<T, pS> const &arr);

  template <class T, class pS>
  decltype(std::declval<T>() + 1.) median(types::ndarray<T, pS> &&arr);

  NUMPY_EXPR_TO_NDARRAY0_DECL(median);

  DEFINE_FUNCTOR(pythonic::numpy, median);
}
PYTHONIC_NS_END

#endif
