#ifndef PYTHONIC_INCLUDE_NUMPY_MEDIAN_HPP
#define PYTHONIC_INCLUDE_NUMPY_MEDIAN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/numpy/asarray.hpp"
#include <algorithm>

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    decltype(std::declval<T>() + 1.) median(types::ndarray<T, N> const &arr);

    template <class T, size_t N>
    decltype(std::declval<T>() + 1.) median(types::ndarray<T, N> &&arr);

    NUMPY_EXPR_TO_NDARRAY0_DECL(median);

    DECLARE_FUNCTOR(pythonic::numpy, median);
  }
}

#endif
