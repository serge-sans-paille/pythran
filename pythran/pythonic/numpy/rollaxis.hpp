#ifndef PYTHONIC_NUMPY_ROLLAXIS_HPP
#define PYTHONIC_NUMPY_ROLLAXIS_HPP

#include "pythonic/include/numpy/rollaxis.hpp"

#include "pythonic/numpy/transpose.hpp"
#include "pythonic/numpy/copy.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T, class pS>
  types::ndarray<T, types::make_pshape_t<std::tuple_size<pS>::value>>
  rollaxis(types::ndarray<T, pS> const &a, long axis, long start)
  {
    auto constexpr N = std::tuple_size<pS>::value;
    if (start >= axis)
      return copy(a);
    long t[N];
    for (long i = 0; i < start; ++i)
      t[i] = i;
    t[start] = axis;
    for (long i = start + 1; i <= axis; ++i)
      t[i] = i - 1;
    for (long i = axis + 1, n = N; i < n; ++i)
      t[i] = i;
    return _transpose(a, t);
  }

  NUMPY_EXPR_TO_NDARRAY0_IMPL(rollaxis);
  DEFINE_FUNCTOR(pythonic::numpy, rollaxis);
}
PYTHONIC_NS_END

#endif
