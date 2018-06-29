#ifndef PYTHONIC_NUMPY_VAR_HPP
#define PYTHONIC_NUMPY_VAR_HPP

#include "pythonic/include/numpy/var.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/add.hpp"
#include "pythonic/numpy/subtract.hpp"
#include "pythonic/numpy/mean.hpp"
#include "pythonic/numpy/sum.hpp"
#include "pythonic/numpy/empty_like.hpp"

#include <algorithm>

PYTHONIC_NS_BEGIN

namespace numpy
{

  template <class E>
  auto var(E const &expr, types::none_type axis, types::none_type dtype,
           types::none_type out, long ddof) -> decltype(var_type<E>(mean(expr)))
  {
    auto m = mean(expr);
    auto t = pythonic::numpy::functor::subtract{}(expr, m);
    return sum(t * t) / var_type<E>(expr.flat_size() - ddof);
  }

  namespace
  {
    // this is a workaround for the lack of efficient support for broadcasting
    // in pythonic
    template <class T, class E, class M>
    void _enlarge_copy_minus(T &&t, E const &e, M const &m, long axis,
                             utils::int_<1>)
    {
      for (long i = 0, n = std::get<0>(e.shape()), p = std::get<0>(m.shape());
           i < n;)
        for (long j = 0; j < p; ++j, ++i)
          t.fast(i) = e.fast(i) - m.fast(j);
    }

    template <class T, class E, class M, size_t N>
    void _enlarge_copy_minus(T &&t, E const &e, M const &m, long axis,
                             utils::int_<N>)
    {
      for (long i = 0, n = std::get<0>(e.shape()), p = std::get<0>(m.shape());
           i < n;)
        for (long j = 0; j < p; ++j, ++i)
          _enlarge_copy_minus(t.fast(i), e.fast(i), m.fast(j), axis,
                              utils::int_<N - 1>());
    }
  }

  template <class E>
  auto var(E const &expr, long axis, types::none_type dtype,
           types::none_type out, long ddof) ->
      typename assignable<decltype(var_type<E>() * mean(expr, axis))>::type
  {
    auto m = mean(expr, axis);
    if (axis == 0) {
      auto t = pythonic::numpy::functor::subtract{}(expr, m);
      return sum(t * t, axis) /= var_type<E>(std::get<0>(expr.shape()) - ddof);
    } else {
      types::array<long, E::value> shp = sutils::array(expr.shape());
      shp[axis] = 1;
      auto mp = m.reshape(shp);

      auto t = empty_like(expr);
      _enlarge_copy_minus(t, expr, mp, axis, utils::int_<E::value>());
      return sum(t * t, axis) /=
             var_type<E>(sutils::array(expr.shape())[axis] - ddof);
    }
  }

  DEFINE_FUNCTOR(pythonic::numpy, var);
}
PYTHONIC_NS_END

#endif
