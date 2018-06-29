#ifndef PYTHONIC_NUMPY_AVERAGE_HPP
#define PYTHONIC_NUMPY_AVERAGE_HPP

#include "pythonic/include/numpy/average.hpp"

#include "pythonic/numpy/asarray.hpp"
#include "pythonic/numpy/sum.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class E>
  auto average(E const &expr, types::none_type const &axis)
      -> decltype(sum(expr, axis) / 1.)
  {
    return sum(expr, axis) / double(expr.flat_size());
  }

  template <class E>
  auto average(E const &expr, long axis) -> decltype(sum(expr, axis) / 1.)
  {
    auto shape = sutils::array(expr.shape());
    return sum(expr, axis) / double(shape[axis]);
  }

  template <class E, class W>
  auto average(E const &expr, types::none_type const &axis, W const &weights)
      -> decltype(average(expr *asarray(weights) / average(asarray(weights))))
  {
    auto aweights = asarray(weights);
    auto weighted_expr = expr * aweights / average(aweights);
    return average(weighted_expr);
  }

  DEFINE_FUNCTOR(pythonic::numpy, average);
}
PYTHONIC_NS_END

#endif
