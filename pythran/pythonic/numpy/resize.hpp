#ifndef PYTHONIC_NUMPY_RESIZE_HPP
#define PYTHONIC_NUMPY_RESIZE_HPP

#include "pythonic/include/numpy/resize.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::ndarray<T, 1> resize(types::ndarray<T, N> const &expr,
                                long new_shape)
    {
      types::ndarray<T, 1> out(types::array<long, N>{{new_shape}},
                               __builtin__::None);
      auto n = expr.flat_size();
      if (n < new_shape) {
        auto iter = std::copy(expr.fbegin(), expr.fend(), out.fbegin());
        for (long i = 1; i < new_shape / n; ++i)
          iter = std::copy(out.fbegin(), out.fbegin() + n, iter);
        std::copy(out.fbegin(), out.fbegin() + new_shape % n, iter);
      } else
        std::copy(expr.fbegin(), expr.fbegin() + new_shape, out.fbegin());
      return out;
    }

    template <class T, size_t N, size_t M>
    types::ndarray<T, M> resize(types::ndarray<T, N> const &expr,
                                types::array<long, M> const &new_shape)
    {
      auto where = std::find(new_shape.begin(), new_shape.end(), -1);
      if (where != new_shape.end()) {
        types::array<long, M> auto_shape(new_shape);
        auto_shape[where - new_shape.begin()] =
            expr.flat_size() / std::accumulate(new_shape.begin(),
                                               new_shape.end(), -1L,
                                               std::multiplies<long>());
        return resize(expr, auto_shape);
      }
      types::ndarray<T, M> out(new_shape, __builtin__::None);
      auto nshape = out.flat_size();
      auto n = expr.flat_size();
      if (n < nshape) {
        auto iter = std::copy(expr.fbegin(), expr.fend(), out.fbegin());
        for (long i = 1; i < nshape / n; ++i)
          iter = std::copy(out.fbegin(), out.fbegin() + n, iter);
        std::copy(out.fbegin(), out.fbegin() + nshape % n, iter);
      } else
        std::copy(expr.fbegin(), expr.fbegin() + nshape, out.fbegin());
      return out;
    }

    NUMPY_EXPR_TO_NDARRAY0_IMPL(resize);
    DEFINE_FUNCTOR(pythonic::numpy, resize);
  }
}

#endif
