#ifndef PYTHONIC_NUMPY_PARTIAL_SUM_HPP
#define PYTHONIC_NUMPY_PARTIAL_SUM_HPP

#include "pythonic/include/numpy/partial_sum.hpp"

#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/neutral.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class Op>
    template <class E, class F, class A>
    A _partial_sum<Op, 1>::operator()(E e, F &o, A acc)
    {
      for (auto const &value : e) {
        Op{}(acc, value);
        *o = acc;
        ++o;
      }
      return acc;
    }

    template <class Op, size_t N>
    template <class E, class F, class A>
    A _partial_sum<Op, N>::operator()(E e, F &o, A acc)
    {
      for (auto const &value : e)
        acc = _partial_sum<Op, N - 1>{}(value, o, acc);
      return acc;
    }

    template <class Op, class E, class dtype>
    types::ndarray<typename dtype::type, 1> partial_sum(E const &expr, dtype d)
    {
      const long count = expr.flat_size();
      types::ndarray<typename dtype::type, 1> the_partial_sum{
          types::make_tuple(count), __builtin__::None};
      auto const p = utils::neutral<Op, typename E::dtype>::value;
      auto iter = the_partial_sum.begin();
      _partial_sum<Op, E::value>{}(expr, iter, p);
      return the_partial_sum;
    }

    template <class Op, class E, class dtype>
    auto partial_sum(E const &expr, long axis, dtype d) ->
        typename std::enable_if<E::value == 1,
                                decltype(partial_sum<Op, E, dtype>(expr))>::type
    {
      if (axis != 0)
        throw types::ValueError("axis out of bounds");
      return partial_sum<Op, E, dtype>(expr);
    }

    template <class Op, class E, class dtype>
    typename std::enable_if<E::value != 1, partial_sum_type<E, dtype>>::type
    partial_sum(E const &expr, long axis, dtype d)
    {
      if (axis < 0 || size_t(axis) >= E::value)
        throw types::ValueError("axis out of bounds");

      auto shape = expr.shape();
      partial_sum_type<E, dtype> the_partial_sum{shape, __builtin__::None};
      if (axis == 0) {
        auto iter = the_partial_sum.begin();
        _partial_sum<Op, 1>{}(
            expr, iter, types::ndarray<typename dtype::type, 1>{
                            types::make_tuple(shape[E::value - 1]),
                            utils::neutral<Op, typename dtype::type>::value});
      } else {
        std::transform(expr.begin(), expr.end(), the_partial_sum.begin(),
                       [axis, d](typename E::iterator::value_type other) {
                         return partial_sum<Op>(other, axis - 1, d);
                       });
      }
      return the_partial_sum;
    }
  }
}

#endif
