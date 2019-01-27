#ifndef PYTHONIC_INCLUDE_NUMPY_TRANSPOSE_HPP
#define PYTHONIC_INCLUDE_NUMPY_TRANSPOSE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"
#include "pythonic/include/utils/nested_container.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  template <class T>
  types::numpy_texpr<types::ndarray<T, types::array<long, 2>>>
  transpose(types::ndarray<T, types::array<long, 2>> const &arr);

  template <class T, class pS0, class pS1>
  types::numpy_texpr<types::ndarray<T, types::pshape<pS0, pS1>>>
  transpose(types::ndarray<T, types::pshape<pS0, pS1>> const &arr);

  template <class T, class pS>
  types::ndarray<T, types::array<long, std::tuple_size<pS>::value>>
  transpose(types::ndarray<T, pS> const &a);

  template <class T, class pS, size_t M>
  types::ndarray<T, types::array<long, std::tuple_size<pS>::value>>
  transpose(types::ndarray<T, pS> const &a, types::array<long, M> const &t);

  NUMPY_EXPR_TO_NDARRAY0_DECL(transpose);
  DEFINE_FUNCTOR(pythonic::numpy, transpose);
}
PYTHONIC_NS_END

#endif
