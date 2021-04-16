#ifndef PYTHONIC_INCLUDE_NUMPY_TRANSPOSE_HPP
#define PYTHONIC_INCLUDE_NUMPY_TRANSPOSE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"
#include "pythonic/include/utils/nested_container.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class E>
  E transpose(types::numpy_texpr<E> const &arr)
  {
    return arr.arg;
  }

  template <class E>
  typename std::enable_if<E::value == 2, types::numpy_texpr<E>>::type
  transpose(E const &arr)
  {
    return {arr};
  }

  template <class E>
  typename std::enable_if<E::value == 1, E>::type transpose(E const &arr)
  {
    return arr;
  }

  template <class T, class pS>
  typename std::enable_if<
      (std::tuple_size<pS>::value > 2),
      types::ndarray<T, types::array<long, std::tuple_size<pS>::value>>>::type
  transpose(types::ndarray<T, pS> const &a);

  template <class T, class pS, size_t M>
  types::ndarray<T, types::array<long, std::tuple_size<pS>::value>>
  transpose(types::ndarray<T, pS> const &a, types::array<long, M> const &t);

  template <class E>
  auto transpose(E const &expr) -> typename std::enable_if<
      (E::value > 2),
      decltype(transpose(types::ndarray<typename E::dtype, typename E::shape_t>{
          expr}))>::type
  {
    return transpose(
        types::ndarray<typename E::dtype, typename E::shape_t>{expr});
  }

  DEFINE_FUNCTOR(pythonic::numpy, transpose);
}
PYTHONIC_NS_END

#endif
