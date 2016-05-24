#ifndef PYTHONIC_TYPES_NUMPY_GEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_GEXPR_HPP

#include "pythonic/include/types/numpy_gexpr.hpp"

#include "pythonic/utils/meta.hpp"
#include "pythonic/operator_/iadd.hpp"
#include "pythonic/operator_/isub.hpp"
#include "pythonic/operator_/imul.hpp"
#include "pythonic/operator_/idiv.hpp"
#ifdef USE_BOOST_SIMD
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/store.hpp>
#endif

namespace pythonic
{

  namespace types
  {
    template <class S0, class S1>
    bool slices_may_overlap(S0 const &s0, S1 const &s1)
    {
      return s0.lower > s1.lower;
    }
    template <class S>
    bool slices_may_overlap(S const &s, long const &i)
    {
      return s.lower <= i and i < s.upper;
    }
    template <class S>
    bool slices_may_overlap(long const &i, S const &s)
    {
      return s.lower <= i and i < s.upper;
    }
    template <class E0, class E1>
    bool may_overlap(E0 const &, E1 const &)
    {
      return true;
    }
    template <class E0, class T0, class T1>
    bool may_overlap(E0 const &, broadcast<T0, T1> const &)
    {
      return false;
    }
    template <class Arg, class E1, class... S>
    typename std::enable_if<std::is_scalar<E1>::value, bool>::type
    may_overlap(numpy_gexpr<Arg, S...> const &gexpr, E1 const &)
    {
      return false;
    }
    template <class Arg, class Tuple, class... S, int... I>
    bool may_overlap_helper(numpy_gexpr<Arg, S...> const &gexpr,
                            Tuple const &args, utils::seq<I...>)
    {
      bool overlaps[] = {may_overlap(gexpr, std::get<I>(args))...};
      return std::any_of(std::begin(overlaps), std::end(overlaps),
                         [](bool b) { return b; });
    }
    template <class Arg, class... E, class... S>
    bool may_overlap(numpy_gexpr<Arg, S...> const &gexpr,
                     numpy_expr<E...> const &expr)
    {
      return may_overlap_helper(gexpr, expr.args,
                                typename utils::gens<sizeof...(E)-1>::type{});
    }
    template <class T, size_t N, class Tp, size_t Np, class... S, class... Sp>
    bool may_overlap(numpy_gexpr<ndarray<T, N> const &, S...> const &gexpr,
                     numpy_gexpr<ndarray<Tp, Np> const &, Sp...> const &expr)
    {
      if (not std::is_same<T, Tp>::value) {
        return false;
      }
      if (N != Np) {
        return false;
      }
      if (gexpr.arg.id() != expr.arg.id()) {
        return false;
      }
      if (not slices_may_overlap(std::get<0>(gexpr.slices),
                                 std::get<0>(expr.slices)))
        return false;
      return true;
    }

    template <class T>
    T to_slice<T>::operator()(T value)
    {
      return value;
    }

    contiguous_slice to_slice<none_type>::operator()(none_type)
    {
      return {none_type{}, none_type{}};
    }

    /* helper to build a new shape out of a shape and a slice with new axis
     */
    template <size_t N, size_t M, size_t C>
    array<long, N> make_reshape(array<long, M> const &shape,
                                array<bool, C> const &is_new_axis)
    {
      array<long, N> new_shape;
      size_t j = 0;
      for (size_t i = 0; i < C; ++i)
        if (is_new_axis[i])
          new_shape[i] = 1;
        else
          new_shape[i] = shape[j++];

      for (size_t i = C; i < N; ++i)
        new_shape[i] = shape[i + j - C];
      return new_shape;
    }

    /* helper to build an extended slice aka numpy_gexpr out of a subscript
     */
    template <size_t C>
    template <class T, size_t N, class... S>
    numpy_gexpr<ndarray<T, N + C>, typename to_slice<S>::type...>
        extended_slice<C>::operator()(ndarray<T, N> &&a, S const &... s)
    {
      return numpy_gexpr<ndarray<T, N + C>, typename to_slice<S>::type...>{
          std::move(a).reshape(make_reshape<N + C>(
              a.shape(),
              array<bool, sizeof...(S)>{to_slice<S>::is_new_axis...})),
          to_slice<S>{}(s)...};
    }

    template <size_t C>
    template <class T, size_t N, class... S>
    numpy_gexpr<ndarray<T, N + C>, typename to_slice<S>::type...>
        extended_slice<C>::operator()(ndarray<T, N> const &a, S const &... s)
    {
      return numpy_gexpr<ndarray<T, N + C>, typename to_slice<S>::type...>{
          a.reshape(make_reshape<N + C>(
              a.shape(),
              array<bool, sizeof...(S)>{{to_slice<S>::is_new_axis...}})),
          to_slice<S>{}(s)...};
    }

    template <class T, size_t N, class... S>
    auto extended_slice<0>::operator()(ndarray<T, N> &&a, long s0,
                                       S const &... s)
        -> decltype(std::declval<numpy_iexpr<ndarray<T, N>>>()(s...))
    {
      return std::move(a)[s0](s...);
    }

    template <class T, size_t N, class... S>
    auto extended_slice<0>::operator()(ndarray<T, N> const &a, long s0,
                                       S const &... s) -> decltype(a[s0](s...))
    {
      return a[s0](s...);
    }

    template <class T, size_t N, class... S>
    numpy_gexpr<ndarray<T, N>, slice, S...> extended_slice<0>::
    operator()(ndarray<T, N> &&a, slice const &s0, S const &... s)
    {
      return numpy_gexpr<ndarray<T, N>, slice, S...>(std::move(a), s0, s...);
    }

    template <class T, size_t N, class... S>
    numpy_gexpr<ndarray<T, N> const &, slice, S...> extended_slice<0>::
    operator()(ndarray<T, N> const &a, slice const &s0, S const &... s)
    {
      return numpy_gexpr<ndarray<T, N> const &, slice, S...>(a, s0, s...);
    }

    template <class T, size_t N, class... S>
    numpy_gexpr<ndarray<T, N>, contiguous_slice, S...> extended_slice<0>::
    operator()(ndarray<T, N> &&a, contiguous_slice const &s0, S const &... s)
    {
      return make_gexpr(std::move(a), s0, s...);
    }

    template <class T, size_t N, class... S>
    numpy_gexpr<ndarray<T, N> const &, contiguous_slice, S...>
        extended_slice<0>::operator()(ndarray<T, N> const &a,
                                      contiguous_slice const &s0,
                                      S const &... s)
    {
      return make_gexpr(a, s0, s...);
    }

    /* manually unrolled copy function
     */

    void flat_copy<0>::operator()(long *, long const *)
    {
    }

    template <size_t I>
    void flat_copy<I>::operator()(long *to, long const *from)
    {
      to[I - 1] = from[I - 1];
      flat_copy<I - 1>()(to, from);
    }

    namespace details
    {

      std::tuple<> const &merge_gexpr<std::tuple<>, std::tuple<>>::
      operator()(std::tuple<> const &t0, std::tuple<> const &)
      {
        return t0;
      }

      template <class... T0>
      std::tuple<T0...> const &merge_gexpr<std::tuple<T0...>, std::tuple<>>::
      operator()(std::tuple<T0...> const &t0, std::tuple<>)
      {
        return t0;
      }

      template <class... T1>
      std::tuple<T1...> const &merge_gexpr<std::tuple<>, std::tuple<T1...>>::
      operator()(std::tuple<>, std::tuple<T1...> const &t1)
      {
        return t1;
      }

      template <class S0, class... T0, class S1, class... T1>
      auto merge_gexpr<std::tuple<S0, T0...>, std::tuple<S1, T1...>>::
      operator()(std::tuple<S0, T0...> const &t0,
                 std::tuple<S1, T1...> const &t1)
          -> decltype(std::tuple_cat(
              std::make_tuple(std::get<0>(t0) * std::get<0>(t1)),
              merge_gexpr<std::tuple<T0...>, std::tuple<T1...>>{}(
                  tuple_tail(t0), tuple_tail(t1))))
      {
        return std::tuple_cat(
            std::make_tuple(std::get<0>(t0) * std::get<0>(t1)),
            merge_gexpr<std::tuple<T0...>, std::tuple<T1...>>{}(
                tuple_tail(t0), tuple_tail(t1)));
      }

      template <class... T0, class S1, class... T1>
      auto merge_gexpr<std::tuple<long, T0...>, std::tuple<S1, T1...>>::
      operator()(std::tuple<long, T0...> const &t0,
                 std::tuple<S1, T1...> const &t1)
          -> decltype(std::tuple_cat(
              std::make_tuple(std::get<0>(t0)),
              merge_gexpr<std::tuple<T0...>, std::tuple<S1, T1...>>{}(
                  tuple_tail(t0), t1)))
      {
        return std::tuple_cat(
            std::make_tuple(std::get<0>(t0)),
            merge_gexpr<std::tuple<T0...>, std::tuple<S1, T1...>>{}(
                tuple_tail(t0), t1));
      }

      template <class S0, class... T0, class... T1>
      auto merge_gexpr<std::tuple<S0, T0...>, std::tuple<long, T1...>>::
      operator()(std::tuple<S0, T0...> const &t0,
                 std::tuple<long, T1...> const &t1)
          -> decltype(std::tuple_cat(
              std::make_tuple(std::get<0>(t1) * std::get<0>(t0).step +
                              std::get<0>(t0).lower),
              merge_gexpr<std::tuple<T0...>, std::tuple<T1...>>{}(
                  tuple_tail(t0), tuple_tail(t1))))
      {
        return std::tuple_cat(
            std::make_tuple(std::get<0>(t1) * std::get<0>(t0).step +
                            std::get<0>(t0).lower),
            merge_gexpr<std::tuple<T0...>, std::tuple<T1...>>{}(
                tuple_tail(t0), tuple_tail(t1)));
      }

      template <class... T0, class... T1>
      auto merge_gexpr<std::tuple<long, T0...>, std::tuple<long, T1...>>::
      operator()(std::tuple<long, T0...> const &t0,
                 std::tuple<long, T1...> const &t1)
          -> decltype(std::tuple_cat(
              std::make_tuple(std::get<0>(t0)),
              merge_gexpr<std::tuple<T0...>, std::tuple<long, T1...>>{}(
                  tuple_tail(t0), t1)))
      {
        return std::tuple_cat(
            std::make_tuple(std::get<0>(t0)),
            merge_gexpr<std::tuple<T0...>, std::tuple<long, T1...>>{}(
                tuple_tail(t0), t1));
      }

      template <class Arg, class... Sp>
      numpy_gexpr<Arg, Sp...> _make_gexpr(Arg arg, std::tuple<Sp...> const &t)
      {
        return {arg, t};
      }

      template <class Arg, class... S>
      numpy_gexpr<Arg, S...> make_gexpr<Arg, S...>::operator()(Arg arg,
                                                               S const &... s)
      {
        return {arg, s...};
      }

      // this specialization is in charge of merging gexpr
      template <class Arg, class... S, class... Sp>
      auto make_gexpr<numpy_gexpr<Arg, S...> const &, Sp...>::
      operator()(numpy_gexpr<Arg, S...> const &arg, Sp const &... s)
          -> decltype(
              _make_gexpr(std::declval<Arg>(),
                          merge_gexpr<std::tuple<S...>, std::tuple<Sp...>>{}(
                              std::tuple<S...>(), std::tuple<Sp...>())))
      {
        return {arg.arg, merge_gexpr<std::tuple<S...>, std::tuple<Sp...>>{}(
                             arg.slices, std::make_tuple(s...))};
      }
    }

    template <class Arg, class... S>
    auto make_gexpr(Arg &&arg, S const &... s)
        -> decltype(details::make_gexpr<Arg, S...>{}(std::forward<Arg>(arg),
                                                     s...))
    {
      return details::make_gexpr<Arg, S...>{}(std::forward<Arg>(arg), s...);
    }

    template <class Arg, class... S>
    array<long, numpy_gexpr<Arg, S...>::value> const &
    numpy_gexpr<Arg, S...>::shape() const
    {
      return _shape;
    }

    template <class Arg, class... S>
    numpy_gexpr<Arg, S...>::numpy_gexpr()
    {
    }

    template <class Arg, class... S>
    template <class Argp> // not using the default one, to make it possible to
    // accept reference and non reference version of Argp
    numpy_gexpr<Arg, S...>::numpy_gexpr(numpy_gexpr<Argp, S...> const &other)
        : arg(other.arg), slices(other.slices), buffer(other.buffer),
          _shape(other.shape()), lower(other.lower), step(other.step),
          indices(other.indices)
    {
      static_assert(std::is_same<typename returnable<Arg>::type,
                                 typename returnable<Argp>::type>::value,
                    "this constructor is only here to adapt reference / non "
                    "reference type, nothing else");
    }

    template <class Arg, class... S>
    template <size_t J, class Slice>
    typename std::enable_if<std::is_same<Slice, slice>::value or
                                std::is_same<Slice, contiguous_slice>::value,
                            void>::type
    numpy_gexpr<Arg, S...>::init_shape(std::tuple<S const &...> const &values,
                                       Slice const &s, utils::int_<1>,
                                       utils::int_<J>)
    {
      auto ns = s.normalize(arg.shape()[sizeof...(S)-1]);
      lower[J] = ns.lower;
      step[J] = ns.step;
      _shape[J] = ns.size();
    }

    template <class Arg, class... S>
    template <size_t I, size_t J, class Slice>
    typename std::enable_if<std::is_same<Slice, slice>::value or
                                std::is_same<Slice, contiguous_slice>::value,
                            void>::type
    numpy_gexpr<Arg, S...>::init_shape(std::tuple<S const &...> const &values,
                                       Slice const &s, utils::int_<I>,
                                       utils::int_<J>)
    {
      auto ns = s.normalize(arg.shape()[sizeof...(S)-I]);
      lower[J] = ns.lower;
      step[J] = ns.step;
      _shape[J] = ns.size();
      init_shape(values, std::get<sizeof...(S)-I + 1>(values),
                 utils::int_<I - 1>(), utils::int_<J + 1>());
    }

    template <class Arg, class... S>
    template <size_t J>
    void
    numpy_gexpr<Arg, S...>::init_shape(std::tuple<S const &...> const &values,
                                       long cs, utils::int_<1>, utils::int_<J>)
    {
      if (cs < 0)
        cs += arg.shape()[sizeof...(S)-1];
      indices[sizeof...(S)-1 - J] = cs;
    }

    template <class Arg, class... S>
    template <size_t I, size_t J>
    void
    numpy_gexpr<Arg, S...>::init_shape(std::tuple<S const &...> const &values,
                                       long cs, utils::int_<I>, utils::int_<J>)
    {
      if (cs < 0)
        cs += arg.shape()[sizeof...(S)-I];
      indices[sizeof...(S)-I - J] = cs;
      init_shape(values, std::get<sizeof...(S)-I + 1>(values),
                 utils::int_<I - 1>(), utils::int_<J>());
    }

    template <class Arg, class... S>
    numpy_gexpr<Arg, S...>::numpy_gexpr(Arg const &arg,
                                        std::tuple<S const &...> const &values)
        : arg(arg), slices(values), buffer(arg.buffer)
    {
      init_shape(values, std::get<0>(values), utils::int_<sizeof...(S)>(),
                 utils::int_<0>());
      for (size_t i = sizeof...(S)-count_long<S...>::value; i < value; ++i)
        _shape[i] = arg.shape()[i + count_long<S...>::value];
    }

    template <class Arg, class... S>
    numpy_gexpr<Arg, S...>::numpy_gexpr(Arg const &arg, S const &... s)
        : numpy_gexpr(arg, std::tuple<S const &...>(s...))
    {
    }

    template <class Arg, class... S>
    template <class Argp, class... Sp>
    numpy_gexpr<Arg, S...>::numpy_gexpr(numpy_gexpr<Argp, Sp...> const &expr,
                                        Arg arg)
        : arg(arg), slices(tuple_pop(expr.slices)), buffer(arg.buffer)
    {
      flat_copy<value>()(&_shape[0], &expr.shape()[1]);
      flat_copy<value>()(&lower[0], &expr.lower[1]);
      flat_copy<value>()(&step[0], &expr.step[1]);
      flat_copy<Arg::value - value>()(&indices[0], &expr.indices[0]);
    }

    template <class Arg, class... S>
    template <class G>
    numpy_gexpr<Arg, S...>::numpy_gexpr(G const &expr, Arg &&arg)
        : arg(std::forward<Arg>(arg)), slices(tuple_pop(expr.slices)),
          buffer(arg.buffer)
    {
      flat_copy<value>()(&_shape[0], &expr.shape()[1]);
      flat_copy<value>()(&lower[0], &expr.lower[1]);
      flat_copy<value>()(&step[0], &expr.step[1]);
    }

    template <class Arg, class... S>
    template <class E>
    typename std::enable_if<may_overlap_gexpr<E>::value,
                            numpy_gexpr<Arg, S...> &>::type
    numpy_gexpr<Arg, S...>::_copy(E const &expr)
    {
      static_assert(value >= utils::dim_of<E>::value, "dimensions match");
      /* at this point, we could not statically check that there is not an
       * aliasing issue that would require an extra copy because of the vector
       * assignment
       * perform a fuzzy alias check dynamically!
       */
      if (may_overlap(*this, expr)) {
        return utils::broadcast_copy<
            numpy_gexpr &, ndarray<typename E::dtype, E::value>, value,
            value - utils::dim_of<E>::value, is_vectorizable>(
            *this, ndarray<typename E::dtype, E::value>{expr});
      } else {
        // 100% sure there's no overlap
        return utils::broadcast_copy < numpy_gexpr &, E, value,
               value - utils::dim_of<E>::value,
               is_vectorizable and
                   is_vectorizable_array<E>::value > (*this, expr);
      }
    }

    template <class Arg, class... S>
    template <class E>
    typename std::enable_if<not may_overlap_gexpr<E>::value,
                            numpy_gexpr<Arg, S...> &>::type
    numpy_gexpr<Arg, S...>::_copy(E const &expr)
    {
      static_assert(value >= utils::dim_of<E>::value, "dimensions match");
      return utils::broadcast_copy < numpy_gexpr &, E, value,
             value - utils::dim_of<E>::value,
             is_vectorizable and
                 is_vectorizable_array<E>::value > (*this, expr);
    }

    template <class Arg, class... S>
    template <class E>
    numpy_gexpr<Arg, S...> &numpy_gexpr<Arg, S...>::operator=(E const &expr)
    {
      return _copy(expr);
    }

    template <class Arg, class... S>
    numpy_gexpr<Arg, S...> &numpy_gexpr<Arg, S...>::
    operator=(numpy_gexpr<Arg, S...> const &expr)
    {
      return _copy(expr);
    }
    template <class Arg, class... S>
    template <class Op, class E>
    typename std::enable_if<not may_overlap_gexpr<E>::value,
                            numpy_gexpr<Arg, S...> &>::type
    numpy_gexpr<Arg, S...>::update_(E const &expr)
    {
      using BExpr =
          typename std::conditional<std::is_scalar<E>::value,
                                    broadcast<E, dtype>, E const &>::type;
      BExpr bexpr = expr;
      // 100% sure there's no overlap
      return utils::broadcast_update < Op, numpy_gexpr &, BExpr, value,
             value - (std::is_scalar<E>::value + utils::dim_of<E>::value),
             is_vectorizable and types::is_vectorizable<E>::value and
                 std::is_same<dtype,
                              typename std::decay<BExpr>::type::dtype>::value >
                     (*this, bexpr);
    }

    template <class Arg, class... S>
    template <class Op, class E>
    typename std::enable_if<may_overlap_gexpr<E>::value,
                            numpy_gexpr<Arg, S...> &>::type
    numpy_gexpr<Arg, S...>::update_(E const &expr)
    {
      using BExpr =
          typename std::conditional<std::is_scalar<E>::value,
                                    broadcast<E, dtype>, E const &>::type;
      BExpr bexpr = expr;

      if (may_overlap(*this, expr)) {
        using NBExpr =
            ndarray<typename std::remove_reference<BExpr>::type::dtype,
                    std::remove_reference<BExpr>::type::value>;
        return utils::broadcast_update < Op, numpy_gexpr &, NBExpr, value,
               value - (std::is_scalar<E>::value + utils::dim_of<E>::value),
               is_vectorizable and types::is_vectorizable<E>::value and
                   std::is_same<
                       dtype, typename std::decay<BExpr>::type::dtype>::value >
                       (*this, NBExpr(bexpr));
      } else {
        // 100% sure there's no overlap
        return utils::broadcast_update < Op, numpy_gexpr &, BExpr, value,
               value - (std::is_scalar<E>::value + utils::dim_of<E>::value),
               is_vectorizable and types::is_vectorizable<E>::value and
                   std::is_same<
                       dtype, typename std::decay<BExpr>::type::dtype>::value >
                       (*this, bexpr);
      }
    }

    template <class Arg, class... S>
    template <class E>
    numpy_gexpr<Arg, S...> &numpy_gexpr<Arg, S...>::operator+=(E const &expr)
    {
      return update_<pythonic::operator_::functor::iadd>(expr);
    }

    template <class Arg, class... S>
    numpy_gexpr<Arg, S...> &numpy_gexpr<Arg, S...>::
    operator+=(numpy_gexpr<Arg, S...> const &expr)
    {
      return update_<pythonic::operator_::functor::iadd>(expr);
    }

    template <class Arg, class... S>
    template <class E>
    numpy_gexpr<Arg, S...> &numpy_gexpr<Arg, S...>::operator-=(E const &expr)
    {
      return update_<pythonic::operator_::functor::isub>(expr);
    }

    template <class Arg, class... S>
    numpy_gexpr<Arg, S...> &numpy_gexpr<Arg, S...>::
    operator-=(numpy_gexpr<Arg, S...> const &expr)
    {
      return update_<pythonic::operator_::functor::isub>(expr);
    }

    template <class Arg, class... S>
    template <class E>
    numpy_gexpr<Arg, S...> &numpy_gexpr<Arg, S...>::operator*=(E const &expr)
    {
      return update_<pythonic::operator_::functor::imul>(expr);
    }

    template <class Arg, class... S>
    numpy_gexpr<Arg, S...> &numpy_gexpr<Arg, S...>::
    operator*=(numpy_gexpr<Arg, S...> const &expr)
    {
      return update_<pythonic::operator_::functor::imul>(expr);
    }

    template <class Arg, class... S>
    template <class E>
    numpy_gexpr<Arg, S...> &numpy_gexpr<Arg, S...>::operator/=(E const &expr)
    {
      return update_<pythonic::operator_::functor::idiv>(expr);
    }

    template <class Arg, class... S>
    numpy_gexpr<Arg, S...> &numpy_gexpr<Arg, S...>::
    operator/=(numpy_gexpr<Arg, S...> const &expr)
    {
      return update_<pythonic::operator_::functor::idiv>(expr);
    }

    template <class Arg, class... S>
    typename numpy_gexpr<Arg, S...>::const_iterator
    numpy_gexpr<Arg, S...>::begin() const
    {
      return make_const_nditerator < is_strided or
             value != 1 > ()(*this, (is_strided or value != 1) ? 0 : lower[0]);
    }

    template <class Arg, class... S>
    typename numpy_gexpr<Arg, S...>::const_iterator
    numpy_gexpr<Arg, S...>::end() const
    {
      return make_const_nditerator < is_strided or
             value !=
                 1 > ()(*this, ((is_strided or value != 1) ? 0 : lower[0]) +
                                   _shape[0]);
    }

    template <class Arg, class... S>
    typename numpy_gexpr<Arg, S...>::iterator numpy_gexpr<Arg, S...>::begin()
    {
      return make_nditerator < is_strided or
             value != 1 > ()(*this, (is_strided or value != 1) ? 0 : lower[0]);
    }

    template <class Arg, class... S>
    typename numpy_gexpr<Arg, S...>::iterator numpy_gexpr<Arg, S...>::end()
    {
      return make_nditerator < is_strided or
             value !=
                 1 > ()(*this, ((is_strided or value != 1) ? 0 : lower[0]) +
                                   _shape[0]);
    }

    template <class Arg, class... S>
    auto numpy_gexpr<Arg, S...>::fast(long i) const
        -> decltype(numpy_gexpr_helper<Arg, S...>::get(*this, i))
    {
      return numpy_gexpr_helper<Arg, S...>::get(
          *this, lower[0] + (is_contiguous<S...>::value ? i : step[0] * i));
    }

    template <class Arg, class... S>
    auto numpy_gexpr<Arg, S...>::fast(long i)
        -> decltype(numpy_gexpr_helper<Arg, S...>::get(*this, i))
    {
      return numpy_gexpr_helper<Arg, S...>::get(
          *this, lower[0] + (is_contiguous<S...>::value ? i : step[0] * i));
    }

#ifdef USE_BOOST_SIMD
    template <class Arg, class... S>
    typename numpy_gexpr<Arg, S...>::simd_iterator
    numpy_gexpr<Arg, S...>::vbegin() const
    {
      return {*this, 0};
    }

    template <class Arg, class... S>
    typename numpy_gexpr<Arg, S...>::simd_iterator
    numpy_gexpr<Arg, S...>::vend() const
    {
      using vector_type =
          typename boost::simd::native<dtype, BOOST_SIMD_DEFAULT_EXTENSION>;
      static const std::size_t vector_size =
          boost::simd::meta::cardinal_of<vector_type>::value;
      return {*this, long(_shape[0] / vector_size * vector_size)};
    }
    template <class Arg, class... S>
    template <class I>
    auto numpy_gexpr<Arg, S...>::load(I i) const -> decltype(boost::simd::load<
        boost::simd::native<dtype, BOOST_SIMD_DEFAULT_EXTENSION>>(this->buffer,
                                                                  i))
    {
      using T = dtype;
      using vT = typename boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>;
      return boost::simd::load<vT>(buffer, lower[0] + i);
    }

    template <class Arg, class... S>
    template <class V>
    void numpy_gexpr<Arg, S...>::store(V &&v, long i)
    {
      boost::simd::store(v, buffer, lower[0] + i);
    }

#endif

    template <class Arg, class... S>
    auto numpy_gexpr<Arg, S...>::operator[](long i) const
        -> decltype(this->fast(i))
    {
      if (i < 0)
        i += _shape[0];
      return fast(i);
    }

    template <class Arg, class... S>
    auto numpy_gexpr<Arg, S...>::operator[](long i) -> decltype(this->fast(i))
    {
      if (i < 0)
        i += _shape[0];
      return fast(i);
    }

    template <class Arg, class... S>
    auto numpy_gexpr<Arg, S...>::operator()(long i) const
        -> decltype((*this)[i])
    {
      return (*this)[i];
    }

    template <class Arg, class... S>
    auto numpy_gexpr<Arg, S...>::operator()(long i) -> decltype((*this)[i])
    {
      return (*this)[i];
    }

    template <class Arg, class... S>
    template <class... Sp>
    auto numpy_gexpr<Arg, S...>::operator()(contiguous_slice const &s0,
                                            Sp const &... s) const
        -> decltype(make_gexpr(*this, s0, s...))
    {
      return make_gexpr(*this, s0, s...);
    }

    template <class Arg, class... S>
    auto numpy_gexpr<Arg, S...>::operator[](contiguous_slice const &s0) const
        -> decltype(make_gexpr(*this, s0))
    {
      return make_gexpr(*this, s0);
    }

    template <class Arg, class... S>
    template <class... Sp>
    auto numpy_gexpr<Arg, S...>::operator()(slice const &s0,
                                            Sp const &... s) const
        -> decltype(make_gexpr(*this, s0, s...))
    {
      return make_gexpr(*this, s0, s...);
    }

    template <class Arg, class... S>
    auto numpy_gexpr<Arg, S...>::operator[](slice const &s0) const
        -> decltype(make_gexpr(*this, s0))
    {
      return make_gexpr(*this, s0);
    }

    template <class Arg, class... S>
    template <class... Sp>
    auto numpy_gexpr<Arg, S...>::operator()(long i, Sp const &... s) const
        -> decltype(std::declval<value_type>()(s...))
    {
      return (*this)[i](s...);
    }

    template <class Arg, class... S>
    template <size_t M>
    auto numpy_gexpr<Arg, S...>::operator[](array<long, M> const &indices) const
        & -> decltype(nget<M - 1>()(*this, indices))
    {
      return nget<M - 1>()(*this, indices);
    }

    template <class Arg, class... S>
        template <size_t M>
        auto numpy_gexpr<Arg, S...>::
        operator[](array<long, M> const &indices) &&
        -> decltype(nget<M - 1>()(std::move(*this), indices))
    {
      return nget<M - 1>()(std::move(*this), indices);
    }

    template <class Arg, class... S>
    template <class F>
    typename std::enable_if<is_numexpr_arg<F>::value,
                            numpy_fexpr<numpy_gexpr<Arg, S...>, F>>::type
    numpy_gexpr<Arg, S...>::fast(F const &filter) const
    {
      return numpy_fexpr<numpy_gexpr, F>(*this, filter);
    }

    template <class Arg, class... S>
    template <class F>
    typename std::enable_if<is_numexpr_arg<F>::value,
                            numpy_fexpr<numpy_gexpr<Arg, S...>, F>>::type
        numpy_gexpr<Arg, S...>::
        operator[](F const &filter) const
    {
      return fast(filter);
    }

    template <class Arg, class... S>
    long numpy_gexpr<Arg, S...>::flat_size() const
    {
      return std::accumulate(_shape.begin() + 1, _shape.end(), *_shape.begin(),
                             std::multiplies<long>());
    }

    // As gexpr has to begin with a slice. When we access it, we need to forward
    // the firsts accessed information
    // to an iexpr until the value in S... is a slice again.
    template <class Arg, class S0, class S1, class... S>
    typename numpy_gexpr_helper<Arg, S0, S1, S...>::type
    numpy_gexpr_helper<Arg, S0, S1, S...>::get(
        numpy_gexpr<Arg, S0, S1, S...> const &e, long i)
    {
      return type(e, numpy_iexpr<Arg const &>(e.arg, i));
    }

    template <class Arg, class S0, class S1, class... S>
    typename numpy_gexpr_helper<Arg, S0, S1, S...>::type
    numpy_gexpr_helper<Arg, S0, S1, S...>::get(
        numpy_gexpr<Arg, S0, S1, S...> &e, long i)
    {
      return type(e, numpy_iexpr<Arg const &>(e.arg, i));
    }

    // Compute forwarding of "long" index to iexpr until we reach a new slice in
    // S... parameters
    namespace
    {

      // We reach a new slice so we have a new gexpr
      template <size_t N, class Arg, class... S>
      template <class E, class F>
      typename finalize_numpy_gexpr_helper<N, Arg, contiguous_slice, S...>::type
      finalize_numpy_gexpr_helper<N, Arg, contiguous_slice, S...>::get(
          E const &e, F &&f)
      {
        return {e, std::forward<F>(f)};
      }

      // We reach a new slice so we have a new gexpr
      template <size_t N, class Arg, class... S>
      template <class E, class F>
      typename finalize_numpy_gexpr_helper<N, Arg, slice, S...>::type
      finalize_numpy_gexpr_helper<N, Arg, slice, S...>::get(E const &e, F &&f)
      {
        return type(e, std::forward<F>(f));
      }

      // We have a long index so it is not a gexpr but a iexpr.
      // We declare a new iexpr and we continue looking for a new slice.
      template <size_t N, class Arg, class... S>
      template <class E, class F>
      auto finalize_numpy_gexpr_helper<N, Arg, long, S...>::get(E const &e,
                                                                F &&f)
          -> decltype(finalize_numpy_gexpr_helper<
              N + 1, numpy_iexpr<Arg const &>,
              S...>::get(e, std::declval<numpy_iexpr<Arg const &>>()))
      {
        return finalize_numpy_gexpr_helper<N + 1, numpy_iexpr<Arg const &>,
                                           S...>::get(e,
                                                      numpy_iexpr<Arg const &>(
                                                          std::forward<F>(f),
                                                          e.indices[N]));
      }

      template <size_t N, class Arg, class... S>
      template <class E, class F>
      auto finalize_numpy_gexpr_helper<N, Arg, long, S...>::get(E &e, F &&f)
          -> decltype(finalize_numpy_gexpr_helper<
              N + 1, numpy_iexpr<Arg const &>,
              S...>::get(e, std::declval<numpy_iexpr<Arg const &> &>()))
      {
        numpy_iexpr<Arg const &> iexpr(std::forward<F>(f), e.indices[N]);
        return finalize_numpy_gexpr_helper<N + 1, numpy_iexpr<Arg const &>,
                                           S...>::get(e, iexpr);
      }

      // If it was a single sliced array, we can return the matching iexpr.
      template <size_t N, class Arg>
      template <class E, class F>
      auto finalize_numpy_gexpr_helper<N, Arg, long>::get(E const &e,
                                                          F const &f)
          -> decltype(numpy_iexpr_helper<F, Arg::value>::get(f, 0))
      {
        return numpy_iexpr_helper<F, Arg::value>::get(f, e.indices[N]);
      }

      template <size_t N, class Arg>
      template <class E, class F>
      auto finalize_numpy_gexpr_helper<N, Arg, long>::get(E const &e, F &f)
          -> decltype(numpy_iexpr_helper<F, Arg::value>::get(f, 0))
      {
        return numpy_iexpr_helper<F, Arg::value>::get(f, e.indices[N]);
      }
    }

    // forward new combination of gexpr/iexpr computation to
    // finalize_numpy_gexpr_helper
    template <class Arg, class S0, class... S>
    auto numpy_gexpr_helper<Arg, S0, long, S...>::get(
        numpy_gexpr<Arg, S0, long, S...> const &e, long i)
        -> decltype(finalize_numpy_gexpr_helper<
            0, numpy_iexpr<Arg const &>, long,
            S...>::get(e, std::declval<numpy_iexpr<Arg const &>>()))
    {
      return finalize_numpy_gexpr_helper<0, numpy_iexpr<Arg const &>, long,
                                         S...>::get(e,
                                                    numpy_iexpr<Arg const &>(
                                                        e.arg, i));
    }

    template <class Arg, class S0, class... S>
    auto numpy_gexpr_helper<Arg, S0, long, S...>::get(
        numpy_gexpr<Arg, S0, long, S...> &e, long i)
        -> decltype(finalize_numpy_gexpr_helper<
            0, numpy_iexpr<Arg const &>, long,
            S...>::get(e, std::declval<numpy_iexpr<Arg const &> &>()))
    {
      return finalize_numpy_gexpr_helper<0, numpy_iexpr<Arg const &>, long,
                                         S...>::get(e,
                                                    numpy_iexpr<Arg const &>(
                                                        e.arg, i));
    }

    // If we have no more slice later, we can say it is an iexpr (We look only
    // for one last long? Not many last long?)
    template <class Arg, class S>
    auto numpy_gexpr_helper<Arg, S, long>::get(
        numpy_gexpr<Arg, S, long> const &e, long i)
        -> decltype(numpy_iexpr_helper<numpy_iexpr<Arg const &>,
                                       numpy_iexpr<Arg const &>::value>::
                        get(std::declval<numpy_iexpr<Arg const &>>(), 0))
    {
      return numpy_iexpr_helper<
          numpy_iexpr<Arg const &>,
          numpy_iexpr<Arg const &>::value>::get(numpy_iexpr<Arg const &>(e.arg,
                                                                         i),
                                                e.indices[0]);
    }

    template <class Arg, class S>
    auto numpy_gexpr_helper<Arg, S, long>::get(numpy_gexpr<Arg, S, long> &e,
                                               long i)
        -> decltype(numpy_iexpr_helper<numpy_iexpr<Arg const &>,
                                       numpy_iexpr<Arg const &>::value>::
                        get(std::declval<numpy_iexpr<Arg const &> &>(), 0))
    {
      numpy_iexpr<Arg const &> iexpr(e.arg, i);
      return numpy_iexpr_helper<
          numpy_iexpr<Arg const &>,
          numpy_iexpr<Arg const &>::value>::get(iexpr, e.indices[0]);
    }
  }
}

#endif
