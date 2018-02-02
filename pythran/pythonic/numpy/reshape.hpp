#ifndef PYTHONIC_NUMPY_RESHAPE_HPP
#define PYTHONIC_NUMPY_RESHAPE_HPP

#include "pythonic/include/numpy/reshape.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T, size_t N, size_t M>
  types::ndarray<T, M> reshape(types::ndarray<T, N> const &expr,
                               types::array<long, M> const &new_shape)
  {
    auto where = std::find(new_shape.begin(), new_shape.end(), -1);
    if (where != new_shape.end()) {
      auto auto_shape = new_shape;
      auto_shape[where - new_shape.begin()] =
          expr.flat_size() / std::accumulate(new_shape.begin(), new_shape.end(),
                                             -1L, std::multiplies<long>());
      return expr.reshape(auto_shape);
    } else
      return expr.reshape(new_shape);
  }

  template <class T, size_t N, class... S>
  auto reshape(types::ndarray<T, N> const &expr, S const &... indices)
      -> decltype(reshape<T, N, sizeof...(S)>(
          expr, types::array<long, sizeof...(S)>{{indices...}}))
  {
    return reshape<T, N, sizeof...(S)>(
        expr, types::array<long, sizeof...(S)>{{indices...}});
  }

  NUMPY_EXPR_TO_NDARRAY0_IMPL(reshape);

  DEFINE_FUNCTOR(pythonic::numpy, reshape);
}
PYTHONIC_NS_END

#endif
