#ifndef PYTHONIC_NUMPY_REDUCE_HPP
#define PYTHONIC_NUMPY_REDUCE_HPP

#include "pythonic/include/numpy/reduce.hpp"

#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/utils/neutral.hpp"

#ifdef USE_BOOST_SIMD
#include <boost/simd/include/functions/broadcast.hpp>
#include <boost/simd/memory/functions/aligned_store.hpp>
#endif

#include <algorithm>

namespace pythonic
{

  namespace numpy
  {
    template <class Op, size_t N, bool vector_form>
    struct _reduce {
      template <class E, class F>
      F operator()(E e, F acc)
      {
        for (auto const &value : e)
          acc = _reduce<Op, N - 1, vector_form>{}(value, acc);
        return acc;
      }
    };

    template <class Op, bool vector_form>
    struct _reduce<Op, 1, vector_form> {
      template <class E, class F>
      F operator()(E e, F acc)
      {
        for (auto const &value : e)
          Op{}(acc, value);
        return acc;
      }
    };

#ifdef USE_BOOST_SIMD
    template <class Op>
    struct _reduce<Op, 1, true> {
      template <class E, class F>
      F operator()(E e, F acc)
      {
        using T = typename E::dtype;
        using vT =
            typename boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>;
        static const size_t vN = boost::simd::meta::cardinal_of<vT>::value;
        const long n = e.size();
        auto viter = e.vbegin(), vend = e.vend();
        const long bound = std::distance(viter, vend);
        ;
        if (bound > 0) {
          auto vacc = *viter;
          ++viter;
          for (long i = 1; i < bound; ++i, ++viter)
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
    };
#endif

    template <class Op, class E>
    typename std::enable_if<types::is_numexpr_arg<E>::value,
                            reduce_result_type<E>>::type
    reduce(E const &expr, types::none_type)
    {
      bool constexpr is_vectorizable =
          E::is_vectorizable and
          not std::is_same<typename E::dtype, bool>::value;
      reduce_result_type<E> p = utils::neutral<Op, typename E::dtype>::value;
      return _reduce<Op, E::value, is_vectorizable>{}(expr, p);
    }

    template <class Op, class E>
    typename std::enable_if<
        std::is_scalar<E>::value or types::is_complex<E>::value, E>::type
    reduce(E const &expr, types::none_type)
    {
      return expr;
    }

    template <class Op, class E>
    auto reduce(E const &array, long axis) ->
        typename std::enable_if<std::is_scalar<E>::value or
                                    types::is_complex<E>::value,
                                decltype(reduce<Op>(array))>::type
    {
      if (axis != 0)
        throw types::ValueError("axis out of bounds");
      return reduce<Op>(array);
    }

    template <class Op, class E>
    auto reduce(E const &array, long axis) ->
        typename std::enable_if<E::value == 1,
                                decltype(reduce<Op>(array))>::type
    {
      if (axis != 0)
        throw types::ValueError("axis out of bounds");
      return reduce<Op>(array);
    }

    template <class Op, class E>
    typename std::enable_if<E::value != 1, reduced_type<E>>::type
    reduce(E const &array, long axis)
    {
      if (axis < 0)
        axis += E::value;
      if (axis < 0 || size_t(axis) >= E::value)
        throw types::ValueError("axis out of bounds");
      auto shape = array.shape();
      if (axis == 0) {
        types::array<long, E::value - 1> shp;
        std::copy(shape.begin() + 1, shape.end(), shp.begin());
        return _reduce<Op, 1, false /* not on scalars*/>{}(
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
  }
}

#endif
