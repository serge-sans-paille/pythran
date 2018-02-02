#ifndef PYTHONIC_INCLUDE_NUMPY_RESHAPE_HPP
#define PYTHONIC_INCLUDE_NUMPY_RESHAPE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"
#include "pythonic/include/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T, size_t N, size_t M>
  types::ndarray<T, M> reshape(types::ndarray<T, N> const &expr,
                               types::array<long, M> const &new_shape);

  template <class T, size_t N, class... S>
  auto reshape(types::ndarray<T, N> const &expr, S const &... indices)
      -> decltype(reshape<T, N, sizeof...(S)>(
          expr, types::array<long, sizeof...(S)>{{indices...}}));

  NUMPY_EXPR_TO_NDARRAY0_DECL(reshape);

  DECLARE_FUNCTOR(pythonic::numpy, reshape);
}
PYTHONIC_NS_END

#endif
