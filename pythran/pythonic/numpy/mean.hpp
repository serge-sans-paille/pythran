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
  template <class E>
  auto mean(E const &expr, types::none_type axis, types::none_type d,
            types::none_type out, std::false_type keepdims)
      -> decltype(sum(expr) / double(expr.flat_size()))
  {
    return sum(expr) / double(expr.flat_size());
  }

  template <class E, class dtype>
  auto mean(E const &expr, types::none_type axis, dtype d, types::none_type out,
            std::false_type keepdims)
      -> decltype(sum(expr) / typename dtype::type(expr.flat_size()))
  {
    return sum(expr) / typename dtype::type(expr.flat_size());
  }

  template <class E>
  auto mean(E const &expr, long axis, types::none_type d, types::none_type out,
            std::false_type keepdims) -> decltype(sum(expr, axis))
  {
    return sum(expr, axis) /= double(sutils::getshape(expr)[axis]);
  }

  // FIXME: need to implement dtype support for numpy::sum / numpy::reduce
  // template <class E, class dtype>
  // auto mean(E const &expr, long axis, dtype d, types::none_type out,
  // std::false_type keepdims)
  //     -> decltype(sum(expr, axis, d))
  // {
  //   return sum(expr, axis, d) /=
  //          typename dtype::type(sutils::getshape(expr)[axis]);
  // }

  template <class E>
  types::ndarray<double, typename details::make_scalar_pshape<E::value>::type>
  mean(E const &expr, types::none_type axis, types::none_type d,
       types::none_type out, std::true_type keep_dims)
  {
    return {typename details::make_scalar_pshape<E::value>::type(),
            mean(expr, axis, d, out)};
  }

  template <class E, class dtype>
  types::ndarray<typename dtype::type,
                 typename details::make_scalar_pshape<E::value>::type>
  mean(E const &expr, types::none_type axis, dtype d, types::none_type out,
       std::true_type keep_dims)
  {
    return {typename details::make_scalar_pshape<E::value>::type(),
            mean(expr, axis, d, out)};
  }

  template <class E>
  auto mean(E const &expr, long axis, types::none_type d, types::none_type out,
            std::true_type keepdims)
      -> decltype(expand_dims(mean(expr, axis), axis))
  {
    return expand_dims(mean(expr, axis), axis);
  }

  // FIXME: need to implement dtype support for numpy::sum / numpy::reduce
  // template <class E, class dtype>
  // auto mean(E const &expr, long axis, dtype d, types::none_type out,
  // std::true_type keepdims)
  //     -> decltype(expand_dims(mean(expr, axis, d), axis))
  // {
  //   return expand_dims(mean(expr, axis, d), axis);
  // }
}
PYTHONIC_NS_END

#endif
