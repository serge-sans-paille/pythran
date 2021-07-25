#ifndef PYTHONIC_INCLUDE_NUMPY_MEAN_HPP
#define PYTHONIC_INCLUDE_NUMPY_MEAN_HPP

#include "pythonic/include/numpy/sum.hpp"
#include "pythonic/include/numpy/expand_dims.hpp"
#include "pythonic/include/builtins/None.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace details
  {
    template <size_t N>
    struct make_scalar_pshape
        : sutils::concat<types::pshape<std::integral_constant<long, 1>>,
                         typename make_scalar_pshape<N - 1>::type> {
    };

    template <>
    struct make_scalar_pshape<1> {
      using type = types::pshape<std::integral_constant<long, 1>>;
    };
  }
  template <class E>
  auto mean(E const &expr, types::none_type axis = {}, types::none_type d = {},
            types::none_type out = {}, std::false_type keep_dims = {})
      -> decltype(sum(expr) / double(expr.flat_size()));

  template <class E, class dtype>
  auto mean(E const &expr, types::none_type axis, dtype d,
            types::none_type out = {}, std::false_type keep_dims = {})
      -> decltype(sum(expr) / typename dtype::type(expr.flat_size()));

  template <class E>
  auto mean(E const &expr, long axis, types::none_type d = {},
            types::none_type out = {}, std::false_type keep_dims = {})
      -> decltype(sum(expr, axis));

  // FIXME: need to implement dtype support for numpy::sum / numpy::reduce
  // template <class E, class dtype>
  // auto mean(E const &expr, long axis, dtype d, types::none_type out={},
  // std::false_type keep_dims={})
  //     -> decltype(sum(expr, axis, d));

  template <class E>
  types::ndarray<double, typename details::make_scalar_pshape<E::value>::type>
  mean(E const &expr, types::none_type axis, types::none_type d,
       types::none_type out, std::true_type keep_dims);

  template <class E, class dtype>
  types::ndarray<typename dtype::type,
                 typename details::make_scalar_pshape<E::value>::type>
  mean(E const &expr, types::none_type axis, dtype d, types::none_type out,
       std::true_type keep_dims);

  template <class E>
  auto mean(E const &expr, long axis, types::none_type d, types::none_type out,
            std::true_type keep_dims)
      -> decltype(expand_dims(mean(expr, axis), axis));

  // FIXME: need to implement dtype support for numpy::sum / numpy::reduce
  // template <class E, class dtype>
  // auto mean(E const &expr, long axis, dtype d, types::none_type out,
  // std::true_type keep_dims)
  //     -> decltype(expand_dims(mean(expr, axis, d), axis));

  DEFINE_FUNCTOR(pythonic::numpy, mean);
}
PYTHONIC_NS_END

#endif
