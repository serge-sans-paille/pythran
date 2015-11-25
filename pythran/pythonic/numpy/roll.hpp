#ifndef PYTHONIC_NUMPY_ROLL_HPP
#define PYTHONIC_NUMPY_ROLL_HPP

#include "pythonic/include/numpy/roll.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, size_t N>
    types::ndarray<T, N> roll(types::ndarray<T, N> const &expr, long shift)
    {
      while (shift < 0)
        shift += expr.flat_size();
      shift %= expr.flat_size();
      types::ndarray<T, N> out(expr.shape(), __builtin__::None);
      std::copy(expr.fbegin(), expr.fend() - shift,
                std::copy(expr.fend() - shift, expr.fend(), out.fbegin()));
      return out;
    }

    template <class To, class From, size_t N>
    To _roll(To to, From from, long, long, types::array<long, N> const &,
             utils::int_<0>)
    {
      *to = *from;
      return to + 1;
    }

    template <class To, class From, size_t N, size_t M>
    To _roll(To to, From from, long shift, long axis,
             types::array<long, N> const &shape, utils::int_<M>)
    {
      long n = shape[N - M];
      long offset = std::accumulate(shape.begin() + N - M + 1, shape.end(), 1L,
                                    std::multiplies<long>());
      if (axis == N - M) {
        for (long i = 0; i < shift; ++i)
          to = _roll(to, from + (n - shift + i) * offset, shift, axis, shape,
                     utils::int_<M - 1>());
        for (long i = shift; i < n; ++i)
          to = _roll(to, from + (i - shift) * offset, shift, axis, shape,
                     utils::int_<M - 1>());
      } else
        for (From end = from + n * offset; from != end; from += offset)
          to = _roll(to, from, shift, axis, shape, utils::int_<M - 1>());
      return to;
    }

    template <class T, size_t N>
    types::ndarray<T, N> roll(types::ndarray<T, N> const &expr, long shift,
                              long axis)
    {
      auto &&expr_shape = expr.shape();
      while (shift < 0)
        shift += expr_shape[axis];
      types::ndarray<T, N> out(expr_shape, __builtin__::None);
      _roll(out.fbegin(), expr.fbegin(), shift, axis, expr_shape,
            utils::int_<N>());
      return out;
    }

    NUMPY_EXPR_TO_NDARRAY0_IMPL(roll);
    DEFINE_FUNCTOR(pythonic::numpy, roll);
  }
}

#endif
