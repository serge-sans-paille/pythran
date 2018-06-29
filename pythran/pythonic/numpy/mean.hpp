#ifndef PYTHONIC_NUMPY_MEAN_HPP
#define PYTHONIC_NUMPY_MEAN_HPP

#include "pythonic/include/numpy/mean.hpp"

#include "pythonic/numpy/sum.hpp"
#include "pythonic/__builtin__/None.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class E, class dtype>
  auto mean(E const &expr, types::none_type axis, dtype d)
      -> decltype(sum(expr) / typename dtype::type(expr.flat_size()))
  {
    return sum(expr) / typename dtype::type(expr.flat_size());
  }

  template <class E, class dtype>
  auto mean(E const &expr, long axis, dtype d) -> decltype(sum(expr, axis))
  {
    return sum(expr, axis) /=
           typename dtype::type(sutils::array(expr.shape())[axis]);
  }

  DEFINE_FUNCTOR(pythonic::numpy, mean);
}
PYTHONIC_NS_END

#endif
