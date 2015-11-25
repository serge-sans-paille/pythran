#ifndef PYTHONIC_NUMPY_TILE_HPP
#define PYTHONIC_NUMPY_TILE_HPP

#include "pythonic/include/numpy/tile.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class I, class O>
    void _tile(I begin, I end, O &out, utils::int_<1>)
    {
      out = std::copy(begin, end, out);
    }

    template <class I, class O, size_t N>
    void _tile(I begin, I end, O &out, utils::int_<N>)
    {
      for (; begin != end; ++begin)
        _tile((*begin).begin(), (*begin).end(), out, utils::int_<N - 1>());
    }

    template <class E>
    types::ndarray<typename E::dtype, E::value> tile(E const &expr, int reps)
    {
      size_t n = expr.flat_size();
      types::ndarray<typename E::dtype, E::value> out(
          types::array<long, 1>{{long(n * reps)}}, __builtin__::None);
      auto out_iter = out.fbegin();
      _tile(expr.begin(), expr.end(), out_iter, utils::int_<E::value>());
      for (int i = 1; i < reps; ++i)
        out_iter = std::copy(out.fbegin(), out.fbegin() + n, out_iter);
      return out;
    }

    template <class E, size_t N>
    types::ndarray<typename E::dtype, N> tile(E const &expr,
                                              types::array<long, N> const &reps)
    {
      size_t n = expr.flat_size();
      types::array<long, N> shape;
      auto &&expr_shape = expr.shape();
      for (size_t i = 0; i < N; ++i)
        shape[N - i - 1] =
            reps[N - i - 1] * ((E::value > i) ? expr_shape[i] : 1);
      types::ndarray<typename E::dtype, N> out(shape, __builtin__::None);
      auto out_iter = out.fbegin();
      _tile(expr.begin(), expr.end(), out_iter, utils::int_<E::value>());

      size_t nreps = out.flat_size() / n;
      for (size_t i = 1; i < nreps; ++i)
        out_iter = std::copy(out.fbegin(), out.fbegin() + n, out_iter);
      return out;
    }

    DEFINE_FUNCTOR(pythonic::numpy, tile);
  }
}

#endif
