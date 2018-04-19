#ifndef PYTHONIC_NUMPY_TRANSPOSE_HPP
#define PYTHONIC_NUMPY_TRANSPOSE_HPP

#include "pythonic/include/numpy/transpose.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/utils/nested_container.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  template <class T>
  types::numpy_texpr<types::ndarray<T, 2>>
      transpose(types::ndarray<T, 2> const &arr)
  {
    return {arr};
  }
  namespace
  {
    template <class T, size_t N, class O, class Indices, class S, class Perm>
    O const *_transpose(types::ndarray<T, N> &expr, O const *iter,
                        Indices &indices, S const &shape, Perm const &perm,
                        utils::int_<N - 1>)
    {
      for (long i = 0, n = shape[N - 1]; i < n; ++i) {
        indices[perm[N - 1]] = i;
        expr.fast(indices) = *iter++;
      }
      indices[perm[N - 1]] = 0;
      return iter;
    }

    template <class T, size_t N, class O, class Indices, class S, class Perm,
              size_t I>
    typename std::enable_if<N - 1 != I, O const *>::type
    _transpose(types::ndarray<T, N> &expr, O const *iter, Indices &indices,
               S const &shape, Perm const &perm, utils::int_<I>)
    {
      for (long i = 0, n = shape[I]; i < n; ++i) {
        indices[perm[I]] = i;
        iter =
            _transpose(expr, iter, indices, shape, perm, utils::int_<I + 1>());
      }
      indices[perm[I]] = 0;
      return iter;
    }
    template <class T, unsigned long N>
    types::ndarray<T, N> _transpose(types::ndarray<T, N> const &a,
                                    long const l[N])
    {
      auto shape = a.shape();
      types::array<long, N> shp;
      for (unsigned long i = 0; i < N; ++i)
        shp[i] = shape[l[i]];

      types::array<long, N> perm;
      for (long i = 0; i < N; ++i)
        perm[l[i]] = i;

      types::ndarray<T, N> new_array(shp, __builtin__::None);

      auto const *iter = a.buffer;
      types::array<long, N> indices;
      _transpose(new_array, iter, indices, shape, perm, utils::int_<0>{});

      return new_array;
    }
  }

  template <class T, size_t N>
  types::ndarray<T, N> transpose(types::ndarray<T, N> const &a)
  {
    long t[N];
    for (unsigned long i = 0; i < N; ++i)
      t[N - 1 - i] = i;
    return _transpose(a, t);
  }

  template <class T, size_t N, size_t M>
  types::ndarray<T, N> transpose(types::ndarray<T, N> const &a,
                                 types::array<long, M> const &t)
  {
    static_assert(N == M, "axes don't match array");

    long val = t[M - 1];
    if (val >= long(N))
      throw types::ValueError("invalid axis for this array");
    return _transpose(a, &t[0]);
  }

  NUMPY_EXPR_TO_NDARRAY0_IMPL(transpose);
  DEFINE_FUNCTOR(pythonic::numpy, transpose);
}
PYTHONIC_NS_END

#endif
