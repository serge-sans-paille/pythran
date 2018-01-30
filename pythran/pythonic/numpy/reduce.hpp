#ifndef PYTHONIC_NUMPY_REDUCE_HPP
#define PYTHONIC_NUMPY_REDUCE_HPP

#include "pythonic/include/numpy/reduce.hpp"

#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/utils/neutral.hpp"

#ifdef USE_BOOST_SIMD
#include <boost/simd/function/broadcast.hpp>
#include <boost/simd/function/aligned_store.hpp>
#include <boost/simd/pack.hpp>
#include <boost/simd/function/load.hpp>
#include <boost/simd/function/store.hpp>
#endif

#include <algorithm>

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class Op, size_t N, class vector_form>
  struct _reduce {
    template <class E, class F>
    F operator()(E &&e, F acc)
    {
      for (auto &&value : std::forward<E>(e))
        acc = _reduce<Op, N - 1, vector_form>{}(
            std::forward<decltype(value)>(value), acc);
      return acc;
    }
  };

  template <class Op, class vector_form>
  struct _reduce<Op, 1, vector_form> {
    template <class E, class F>
    F operator()(E &&e, F acc)
    {
      for (auto value : std::forward<E>(e)) {
        Op{}(acc, value);
      }
      return acc;
    }
  };

#ifdef USE_BOOST_SIMD
  template <class vectorizer, class Op, class E, class F>
  F vreduce(E e, F acc)
  {
    using T = typename E::dtype;
    using vT = boost::simd::pack<T>;
    static const size_t vN = vT::static_size;
    const long n = e.size();
    auto viter = vectorizer::vbegin(e), vend = vectorizer::vend(e);
    const long bound = std::distance(viter, vend);
    if (bound > 0) {
      auto vacc = *viter;
      for (++viter; viter != vend; ++viter)
        Op{}(vacc, *viter);
      alignas(sizeof(vT)) T stored[vN];
      boost::simd::store(vacc, &stored[0]);
      for (size_t j = 0; j < vN; ++j)
        Op{}(acc, stored[j]);
    }
    auto iter = e.begin() + bound * vN;

    for (long i = bound * vN; i < n; ++i, ++iter) {
      Op{}(acc, *iter);
    }
    return acc;
  }

  template <class Op>
  struct _reduce<Op, 1, types::vectorizer> {
    template <class E, class F>
    F operator()(E &&e, F acc)
    {
      return vreduce<types::vectorizer, Op>(std::forward<E>(e), acc);
    }
  };
  template <class Op>
  struct _reduce<Op, 1, types::vectorizer_nobroadcast> {
    template <class E, class F>
    F operator()(E &&e, F acc)
    {
      return vreduce<types::vectorizer_nobroadcast, Op>(std::forward<E>(e),
                                                        acc);
    }
  };
#endif
  template <class Op, class E, bool vector_form>
  struct reduce_helper;

  template <class Op, class E>
  struct reduce_helper<Op, E, false> {
    reduce_result_type<E> operator()(E const &expr,
                                     reduce_result_type<E> p) const
    {
      return _reduce<Op, E::value, types::novectorize>{}(expr, p);
    }
  };
  template <class Op, class E>
  struct reduce_helper<Op, E, true> {
    reduce_result_type<E> operator()(E const &expr,
                                     reduce_result_type<E> p) const
    {
      if (utils::no_broadcast(expr))
        return _reduce<Op, E::value, types::vectorizer_nobroadcast>{}(expr, p);
      else
        return _reduce<Op, E::value, types::vectorizer>{}(expr, p);
    }
  };

  template <class Op, class E>
  typename std::enable_if<types::is_numexpr_arg<E>::value,
                          reduce_result_type<E>>::type
  reduce(E const &expr, types::none_type)
  {
    bool constexpr is_vectorizable =
        E::is_vectorizable && !std::is_same<typename E::dtype, bool>::value;
    reduce_result_type<E> p = utils::neutral<Op, typename E::dtype>::value;
    return reduce_helper<Op, E, is_vectorizable>{}(expr, p);
  }

  template <class Op, class E>
  typename std::enable_if<
      std::is_scalar<E>::value || types::is_complex<E>::value, E>::type
  reduce(E const &expr, types::none_type)
  {
    return expr;
  }

  template <class Op, class E>
  auto reduce(E const &array, long axis) ->
      typename std::enable_if<std::is_scalar<E>::value ||
                                  types::is_complex<E>::value,
                              decltype(reduce<Op>(array))>::type
  {
    if (axis != 0)
      throw types::ValueError("axis out of bounds");
    return reduce<Op>(array);
  }

  template <class Op, class E>
  auto reduce(E const &array, long axis) ->
      typename std::enable_if<E::value == 1, decltype(reduce<Op>(array))>::type
  {
    if (axis != 0)
      throw types::ValueError("axis out of bounds");
    return reduce<Op>(array);
  }

  template <class Op, class E>
  typename std::enable_if<E::value != 1, reduced_type<E>>::type
  reduce(E const &array, long axis, types::none_type, types::none_type)
  {
    if (axis < 0)
      axis += E::value;
    if (axis < 0 || size_t(axis) >= E::value)
      throw types::ValueError("axis out of bounds");
    auto shape = array.shape();
    if (axis == 0) {
      types::array<long, E::value - 1> shp;
      std::copy(shape.begin() + 1, shape.end(), shp.begin());
      return _reduce<Op, 1, types::novectorize /* ! on scalars*/>{}(
          array,
          reduced_type<E>{shp, utils::neutral<Op, typename E::dtype>::value});
    } else {
      types::array<long, E::value - 1> shp;
      auto next = std::copy(shape.begin(), shape.begin() + axis, shp.begin());
      std::copy(shape.begin() + axis + 1, shape.end(), next);
      reduced_type<E> sumy{shp, __builtin__::None};
      std::transform(array.begin(), array.end(), sumy.begin(),
                     [axis](typename E::const_iterator::value_type other) {
                       return reduce<Op>(other, axis - 1);
                     });
      return sumy;
    }
  }
  template <class Op, class E>
  typename std::enable_if<E::value != 1, reduced_type<E>>::type
  reduce(E const &array, long axis, types::none_type, reduced_type<E> out)
  {
    if (axis < 0)
      axis += E::value;
    if (axis < 0 || size_t(axis) >= E::value)
      throw types::ValueError("axis out of bounds");
    if (axis == 0) {
      std::fill(out.begin(), out.end(),
                utils::neutral<Op, typename E::dtype>::value);
      return _reduce<Op, 1, types::novectorize /* ! on scalars*/>{}(array, out);
    } else {
      std::transform(array.begin(), array.end(), out.begin(),
                     [axis](typename E::const_iterator::value_type other) {
                       return reduce<Op>(other, axis - 1);
                     });
      return out;
    }
  }
}
PYTHONIC_NS_END

#endif
