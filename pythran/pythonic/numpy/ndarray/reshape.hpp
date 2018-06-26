#ifndef PYTHONIC_NUMPY_NDARRAY_RESHAPE_HPP
#define PYTHONIC_NUMPY_NDARRAY_RESHAPE_HPP

#include "pythonic/include/numpy/ndarray/reshape.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace ndarray
  {
    template <class T, class pS, class NpS>
    types::ndarray<T, NpS> reshape(types::ndarray<T, pS> const &expr,
                                   NpS const &new_shape)
    {
      auto auto_shape = new_shape;
      auto where = sutils::find(auto_shape, -1);
      if (where) {
        *where = expr.flat_size() / -sutils::prod(new_shape);
        return expr.reshape(auto_shape);
      } else
        return expr.reshape(new_shape);
    }

    template <class T, class pS, class... S>
    auto reshape(types::ndarray<T, pS> const &expr, S const &... indices)
        -> decltype(reshape(expr, types::pshape<S...>{indices...}))
    {
      return reshape(expr, types::pshape<S...>{indices...});
    }

    NUMPY_EXPR_TO_NDARRAY0_IMPL(reshape);

    DEFINE_FUNCTOR(pythonic::numpy::ndarray, reshape);
  }
}
PYTHONIC_NS_END

#endif
