#ifndef PYTHONIC_NUMPY_MEAN_HPP
#define PYTHONIC_NUMPY_MEAN_HPP

#include "pythonic/include/numpy/mean.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/numpy/asarray.hpp"
#include "pythonic/numpy/expand_dims.hpp"
#include "pythonic/numpy/sum.hpp"
#include "pythonic/builtins/None.hpp"

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
           typename dtype::type(sutils::getshape(expr)[axis]);
  }

  template <class E, class dtype>
  auto mean(E const &expr, types::none_type axis, dtype d, std::false_type keepdims)
      -> decltype(sum(expr) / typename dtype::type(expr.flat_size()))
  {
    return sum(expr) / typename dtype::type(expr.flat_size());
  }

  template <class E, class dtype>
  auto mean(E const &expr, long axis, dtype d, std::false_type keepdims) 
      -> decltype(sum(expr, axis))
  {
    return sum(expr, axis) /=
           typename dtype::type(sutils::getshape(expr)[axis]);
  }

  template <class E, class dtype>
  auto mean(E const &expr, types::none_type axis, dtype d, std::true_type keepdims)
  {
    const long N = E::value;
    types::array<long, N> out_shape;
    std::fill_n (out_shape, N, 1);
    return numpy::functor::asarray{}(sum(expr) / 
           typename dtype::type(expr.flat_size())).reshape(out_shape);
  }

  template <class E, class dtype>
  auto mean(E const &expr, long axis, dtype d, std::true_type keepdims) 
      -> decltype(expand_dims(sum(expr, axis), axis))
  {
    return expand_dims(sum(expr, axis) /=
           typename dtype::type(sutils::getshape(expr)[axis]), axis);
  }
}
PYTHONIC_NS_END

#endif
