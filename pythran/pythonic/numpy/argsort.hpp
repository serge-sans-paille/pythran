#ifndef PYTHONIC_NUMPY_ARGSORT_HPP
#define PYTHONIC_NUMPY_ARGSORT_HPP

#include "pythonic/include/numpy/argsort.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T, class pS>
  types::ndarray<long, pS> argsort(types::ndarray<T, pS> const &a)
  {
    constexpr auto N = std::tuple_size<pS>::value;
    size_t last_axis = std::get<N - 1>(a.shape());
    size_t n = a.flat_size();
    types::ndarray<long, pS> indices(a.shape(), __builtin__::None);
    for (long j = 0, *iter_indices = indices.buffer,
              *end_indices = indices.buffer + n;
         iter_indices != end_indices;
         iter_indices += last_axis, j += last_axis) {
      // fill with the original indices
      std::iota(iter_indices, iter_indices + last_axis, 0L);
      // sort the index using the value from a
      std::sort(iter_indices, iter_indices + last_axis,
                [&a, j](long i1, long i2) {
                  return *(a.fbegin() + j + i1) < *(a.fbegin() + j + i2);
                });
    }
    return indices;
  }

  NUMPY_EXPR_TO_NDARRAY0_IMPL(argsort);
}
PYTHONIC_NS_END

#endif
