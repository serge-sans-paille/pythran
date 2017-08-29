#ifndef PYTHONIC_NUMPY_FLIP_HPP
#define PYTHONIC_NUMPY_FLIP_HPP

#include "pythonic/include/numpy/flip.hpp"

#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"

namespace pythonic
{

  namespace numpy
  {
    namespace
    {
      template <class To, class From, size_t N>
      To _flip(To to, From from, long, types::array<long, N> const &,
               utils::int_<0>)
      {
        *to = *from;
        return to + 1;
      }

      template <class To, class From, size_t N, size_t M>
      To _flip(To to, From from, long axis, types::array<long, N> const &shape,
               utils::int_<M>)
      {
        long n = shape[N - M];
        long offset = std::accumulate(shape.begin() + N - M + 1, shape.end(),
                                      1L, std::multiplies<long>());
        if (axis == N - M) {
          for (long i = 0; i < n; ++i)
            to = _flip(to, from + (n - 1 - i) * offset, axis, shape,
                       utils::int_<M - 1>());
        } else
          for (From end = from + n * offset; from != end; from += offset)
            to = _flip(to, from, axis, shape, utils::int_<M - 1>());
        return to;
      }
    }

    template <class T, size_t N>
    types::ndarray<T, N> flip(types::ndarray<T, N> const &expr, long axis)
    {
      auto &&expr_shape = expr.shape();
      types::ndarray<T, N> out(expr_shape, __builtin__::None);
      _flip(out.fbegin(), expr.fbegin(), axis, expr_shape, utils::int_<N>());
      return out;
    }

    NUMPY_EXPR_TO_NDARRAY0_IMPL(flip);
    DEFINE_FUNCTOR(pythonic::numpy, flip);
  }
}

#endif
