#ifndef PYTHONIC_NUMPY_TILE_HPP
#define PYTHONIC_NUMPY_TILE_HPP

#include "pythonic/include/numpy/tile.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace
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
  }

  template <class E>
  types::ndarray<typename E::dtype, types::array<long, E::value>>
  tile(E const &expr, int reps)
  {
    size_t n = expr.flat_size();
    types::ndarray<typename E::dtype, types::array<long, E::value>> out(
        types::array<long, 1>{{long(n * reps)}}, __builtin__::None);
    auto out_iter = out.fbegin();
    _tile(expr.begin(), expr.end(), out_iter, utils::int_<E::value>());
    for (int i = 1; i < reps; ++i)
      out_iter = std::copy(out.fbegin(), out.fbegin() + n, out_iter);
    return out;
  }

  template <class R, class pS, size_t... Is>
  types::array<long, sizeof...(Is)>
  tile_init_shape(R const &reps, pS const &expr_shape,
                  utils::index_sequence<Is...>)
  {
    constexpr size_t N = std::tuple_size<R>::value;
    return {
        {(reps[Is] * ((std::tuple_size<pS>::value > (N - 1 - Is))
                          ? std::get<((N - 1 - Is < std::tuple_size<pS>::value)
                                          ? (N - 1 - Is)
                                          : 0)>(expr_shape)
                          : 1))...}};
  }

  template <class E, size_t N>
  types::ndarray<typename E::dtype, types::array<long, N>>
  tile(E const &expr, types::array<long, N> const &reps)
  {
    size_t n = expr.flat_size();
    auto &&expr_shape = expr.shape();
    types::array<long, N> shape =
        tile_init_shape(reps, expr_shape, utils::make_index_sequence<N>());
    // for (size_t i = 0; i < N; ++i)
    //  shape[N - i - 1] = reps[N - i - 1] * ((E::value > i) ? expr_shape[i] :
    //  1);
    types::ndarray<typename E::dtype, types::array<long, N>> out(
        shape, __builtin__::None);
    auto out_iter = out.fbegin();
    _tile(expr.begin(), expr.end(), out_iter, utils::int_<E::value>());

    size_t nreps = out.flat_size() / n;
    for (size_t i = 1; i < nreps; ++i)
      out_iter = std::copy(out.fbegin(), out.fbegin() + n, out_iter);
    return out;
  }

  DEFINE_FUNCTOR(pythonic::numpy, tile);
}
PYTHONIC_NS_END

#endif
