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

  template <class T, class pS0, class pS1>
  types::numpy_texpr<types::ndarray<T, types::pshape<pS0, pS1>>>
      transpose(types::ndarray<T, types::pshape<pS0, pS1>> const &arr)
  {
    return {arr};
  }
  namespace
  {
    template <class T, class pS, class O, class Indices, class S, class Perm>
    O const *_transpose(types::ndarray<T, pS> &expr, O const *iter,
                        Indices &indices, S const &shape, Perm const &perm,
                        utils::int_<pS::value - 1>)
    {
      for (long i = 0, n = shape[pS::value - 1]; i < n; ++i) {
        indices[perm[pS::value - 1]] = i;
        expr.fast(indices) = *iter++;
      }
      indices[perm[pS::value - 1]] = 0;
      return iter;
    }

    template <class T, class pS, class O, class Indices, class S, class Perm,
              size_t I>
    typename std::enable_if<pS::value - 1 != I, O const *>::type
    _transpose(types::ndarray<T, pS> &expr, O const *iter, Indices &indices,
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
    template <class T, class pS>
    types::ndarray<T, types::make_pshape_t<pS::value>> _transpose(types::ndarray<T, pS> const &a,
                                    long const l[pS::value])
    {
      auto shape = a.shape();
      types::array<long, pS::value> shp;
      for (unsigned long i = 0; i < pS::value; ++i)
        shp[i] = shape[l[i]];

      types::array<long, pS::value> perm;
      for (long i = 0; i < pS::value; ++i)
        perm[l[i]] = i;

      types::ndarray<T, types::make_pshape_t<pS::value>> new_array(shp, __builtin__::None);

      auto const *iter = a.buffer;
      types::array<long, pS::value> indices;
      _transpose(new_array, iter, indices, shape, perm, utils::int_<0>{});

      return new_array;
    }
  }

  template <class T, class pS>
  types::ndarray<T, types::make_pshape_t<pS::value>> transpose(types::ndarray<T, pS> const &a)
  {
    long t[pS::value];
    for (unsigned long i = 0; i < pS::value; ++i)
      t[pS::value - 1 - i] = i;
    return _transpose(a, t);
  }

  template <class T, class pS, size_t M>
  types::ndarray<T, types::make_pshape_t<pS::value>> transpose(types::ndarray<T, pS> const &a,
                                 types::array<long, M> const &t)
  {
    static_assert(pS::value == M, "axes don't match array");

    long val = t[M - 1];
    if (val >= long(pS::value))
      throw types::ValueError("invalid axis for this array");
    return _transpose(a, &t[0]);
  }

  NUMPY_EXPR_TO_NDARRAY0_IMPL(transpose);
  DEFINE_FUNCTOR(pythonic::numpy, transpose);
}
PYTHONIC_NS_END

#endif
