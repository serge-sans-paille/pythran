#ifndef PYTHONIC_NUMPY_MEDIAN_HPP
#define PYTHONIC_NUMPY_MEDIAN_HPP

#include "pythonic/include/numpy/median.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"
#include <algorithm>

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T, class pS>
  decltype(std::declval<T>() + 1.) median(types::ndarray<T, pS> const &arr)
  {
    size_t n = arr.flat_size();
    T *tmp = new T[n];
    std::copy(arr.buffer, arr.buffer + n, tmp);
    std::sort(tmp, tmp + n);
    auto out = (tmp[n / 2] + tmp[(n - 1) / 2]) / double(2);
    delete[] tmp;
    return out;
  }

  template <class T, class pS>
  decltype(std::declval<T>() + 1.) median(types::ndarray<T, pS> &&arr)
  {
    size_t n = arr.flat_size();
    T *tmp = arr.buffer;
    std::sort(tmp, tmp + n);
    auto out = (tmp[n / 2] + tmp[(n - 1) / 2]) / double(2);
    return out;
  }

  NUMPY_EXPR_TO_NDARRAY0_IMPL(median);

  DEFINE_FUNCTOR(pythonic::numpy, median);
}
PYTHONIC_NS_END

#endif
