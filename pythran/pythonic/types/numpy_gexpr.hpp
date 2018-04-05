#ifndef PYTHONIC_TYPES_NUMPY_GEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_GEXPR_HPP

#include "pythonic/include/types/numpy_gexpr.hpp"

#include "pythonic/utils/meta.hpp"
#include "pythonic/operator_/iadd.hpp"
#include "pythonic/operator_/ior.hpp"
#include "pythonic/operator_/iand.hpp"
#include "pythonic/operator_/isub.hpp"
#include "pythonic/operator_/imul.hpp"
#include "pythonic/operator_/idiv.hpp"

PYTHONIC_NS_BEGIN

namespace types
{
  template <class... S>
  struct count_leading_long;
  template <>
  struct count_leading_long<> {
    static constexpr size_t value = 0;
  };
  template <class... S>
  struct count_leading_long<long, S...> {
    static constexpr size_t value = 1 + count_leading_long<S...>::value;
  };
  template <class... S>
  struct count_leading_long<long const &, S...> {
    static constexpr size_t value = 1 + count_leading_long<S...>::value;
  };
  template <class S0, class... S>
  struct count_leading_long<S0, S...> {
    static constexpr size_t value = 0;
  };

  template <class S0, class S1>
  bool slices_may_overlap(S0 const &s0, S1 const &s1)
  {
    return s0.lower > s1.lower;
  }
  template <class S>
  bool slices_may_overlap(S const &s, long const &i)
  {
    return s.lower <= i && i < s.upper;
  }
  template <class S>
  bool slices_may_overlap(long const &i, S const &s)
  {
    return s.lower <= i && i < s.upper;
  }

  bool slices_may_overlap(long const &i, long const &j)
  {
    return i == j;
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
  template <class Arg, class Tuple, class... S, size_t... I>
  bool may_overlap_helper(numpy_gexpr<Arg, S...> const &gexpr,
                          Tuple const &args, utils::index_sequence<I...>)
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
                              utils::make_index_sequence<sizeof...(E)-1>{});
  }
  template <size_t N, size_t Np, class G, class Gp>
  bool may_overlap_helper(G const &gexpr, Gp const &expr)
  {
    if (!std::is_same<typename G::dtype, typename Gp::dtype>::value) {
      return false;
    }
    if (N != Np) {
      return false;
    }
    if (gexpr.arg.id() != expr.arg.id()) {
      return false;
    }
    if (!slices_may_overlap(std::get<0>(gexpr.slices),
                            std::get<0>(expr.slices)))
      return false;
    return true;
  }

  template <class T, size_t N, class Tp, size_t Np, class... S, class... Sp>
  bool may_overlap(numpy_gexpr<ndarray<T, N> const &, S...> const &gexpr,
                   numpy_gexpr<ndarray<Tp, Np> const &, Sp...> const &expr)
  {
    return may_overlap_helper<N, Np>(gexpr, expr);
  }
  template <class T, size_t N, class Tp, size_t Np, class... S, class... Sp>
  bool may_overlap(numpy_gexpr<ndarray<T, N>, S...> const &gexpr,
                   numpy_gexpr<ndarray<Tp, Np>, Sp...> const &expr)
  {
    return may_overlap_helper<N, Np>(gexpr, expr);
  }
  template <class T, size_t N, class Tp, size_t Np, class... S, class... Sp>
  bool may_overlap(numpy_gexpr<ndarray<T, N> const &, S...> const &gexpr,
                   numpy_gexpr<ndarray<Tp, Np>, Sp...> const &expr)
  {
    return may_overlap_helper<N, Np>(gexpr, expr);
  }
  template <class T, size_t N, class Tp, size_t Np, class... S, class... Sp>
  bool may_overlap(numpy_gexpr<ndarray<T, N>, S...> const &gexpr,
                   numpy_gexpr<ndarray<Tp, Np> const &, Sp...> const &expr)
  {
    return may_overlap_helper<N, Np>(gexpr, expr);
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

  /* helper to build a new shape out of a shape && a slice with new axis
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
  template <size_t C, bool Final>
  template <class T, size_t N, class... S>
  auto extended_slice<C, Final>::operator()(ndarray<T, N> &&a, S const &... s)
      -> decltype(std::declval<ndarray<T, N + C>>()(
          std::declval<typename to_slice<S>::type>()...))
  {
    return std::move(a).reshape(make_reshape<N + C>(
        a.shape(), array<bool, sizeof...(S)>{to_slice<S>::is_new_axis...}))(
        to_slice<S>{}(s)...);
  }

  template <size_t C, bool Final>
  template <class T, size_t N, class... S>
  auto extended_slice<C, Final>::operator()(ndarray<T, N> const &a,
                                            S const &... s)
      -> decltype(std::declval<ndarray<T, N + C>>()(
          std::declval<typename to_slice<S>::type>()...))
  {
    return a.reshape(make_reshape<N + C>(
        a.shape(), array<bool, sizeof...(S)>{{to_slice<S>::is_new_axis...}}))(
        to_slice<S>{}(s)...);
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
    operator()(std::tuple<S0, T0...> const &t0, std::tuple<S1, T1...> const &t1)
        -> decltype(
            std::tuple_cat(std::make_tuple(std::get<0>(t0) * std::get<0>(t1)),
                           merge_gexpr<std::tuple<T0...>, std::tuple<T1...>>{}(
                               tuple_tail(t0), tuple_tail(t1))))
    {
      return std::tuple_cat(std::make_tuple(std::get<0>(t0) * std::get<0>(t1)),
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
          merge_gexpr<std::tuple<T0...>, std::tuple<T1...>>{}(tuple_tail(t0),
                                                              tuple_tail(t1)));
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

    template <class Arg, class... S>
    numpy_gexpr<Arg, S...> make_gexpr<Arg, S...>::operator()(Arg arg,
                                                             S const &... s)
    {
      return {arg, s...};
    }

    // this specialization is in charge of merging gexpr
    template <class Arg, class... S, class... Sp>
    auto make_gexpr<numpy_gexpr<Arg, S...> const &, Sp...>::
    operator()(numpy_gexpr<Arg, S...> const &arg, Sp const &... s) -> decltype(
        std::declval<Arg>()[merge_gexpr<std::tuple<S...>, std::tuple<Sp...>>{}(
            std::tuple<S...>(), std::tuple<Sp...>())])
    {
      return arg.arg[merge_gexpr<std::tuple<S...>, std::tuple<Sp...>>{}(
          arg.slices, std::make_tuple(s...))];
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
  numpy_gexpr<Arg, S...>::numpy_gexpr()
      : buffer(nullptr)
  {
  }

  template <class Arg, class... S>
  template <class Argp> // ! using the default one, to make it possible to
  // accept reference && non reference version of Argp
  numpy_gexpr<Arg, S...>::numpy_gexpr(numpy_gexpr<Argp, S...> const &other)
      : arg(other.arg), slices(other.slices), buffer(other.buffer),
        _shape(other.shape())
  {
    static_assert(std::is_same<typename returnable<Arg>::type,
                               typename returnable<Argp>::type>::value,
                  "this constructor is only here to adapt reference / non "
                  "reference type, nothing else");
  }

  template <class Arg, class... S>
  template <size_t J, class Slice>
  typename std::enable_if<std::is_same<Slice, slice>::value ||
                              std::is_same<Slice, contiguous_slice>::value,
                          void>::type
  numpy_gexpr<Arg, S...>::init_shape(Slice const &s, utils::int_<1>,
                                     utils::int_<J>)
  {
    auto ns = s.normalize(arg._shape[sizeof...(S)-1]);
    std::get<sizeof...(S)-1>(slices).lower = ns.lower;
    _shape[J] = ns.size();
    buffer += ns.lower * arg._strides[sizeof...(S)-1];
    ;
  }

  template <class Arg, class... S>
  template <size_t I, size_t J, class Slice>
  typename std::enable_if<std::is_same<Slice, slice>::value ||
                              std::is_same<Slice, contiguous_slice>::value,
                          void>::type
  numpy_gexpr<Arg, S...>::init_shape(Slice const &s, utils::int_<I>,
                                     utils::int_<J>)
  {
    auto ns = s.normalize(arg._shape[sizeof...(S)-I]);
    std::get<sizeof...(S)-I>(slices).lower = ns.lower;
    _shape[J] = ns.size();
    init_shape(std::get<sizeof...(S)-I + 1>(slices), utils::int_<I - 1>(),
               utils::int_<J + 1>());
    buffer += ns.lower * arg._strides[sizeof...(S)-I];
  }

  template <class Arg, class... S>
  template <size_t J>
  void numpy_gexpr<Arg, S...>::init_shape(long cs, utils::int_<1>,
                                          utils::int_<J>)
  {
    if (cs < 0)
      cs += arg._shape[sizeof...(S)-1];
    std::get<sizeof...(S)-1>(slices) = cs;
    buffer += cs * arg._strides[sizeof...(S)-1];
  }

  template <class Arg, class... S>
  template <size_t I, size_t J>
  void numpy_gexpr<Arg, S...>::init_shape(long cs, utils::int_<I>,
                                          utils::int_<J>)
  {
    if (cs < 0)
      cs += arg._shape[sizeof...(S)-I];
    std::get<sizeof...(S)-I>(slices) = cs;
    init_shape(std::get<sizeof...(S)-I + 1>(slices), utils::int_<I - 1>(),
               utils::int_<J>());
    buffer += cs * arg._strides[sizeof...(S)-I];
  }

  template <class Arg, class... S>
  numpy_gexpr<Arg, S...>::numpy_gexpr(Arg const &arg,
                                      std::tuple<S const &...> const &values)
      : arg(arg), slices(values), buffer(this->arg.buffer)
  {
    init_shape(std::get<0>(slices), utils::int_<sizeof...(S)>(),
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
  template <class E>
  typename std::enable_if<may_overlap_gexpr<E>::value,
                          numpy_gexpr<Arg, S...> &>::type
  numpy_gexpr<Arg, S...>::_copy(E const &expr)
  {
    static_assert(value >= utils::dim_of<E>::value, "dimensions match");
    /* at this point, we could ! statically check that there is ! an
     * aliasing issue that would require an extra copy because of the vector
     * assignment
     * perform a fuzzy alias check dynamically!
     */
    assert(buffer);
    if (may_overlap(*this, expr)) {
      ndarray<typename E::dtype, E::value> tmp = expr;
      return utils::broadcast_copy<
          numpy_gexpr &, ndarray<typename E::dtype, E::value>, value,
          value - utils::dim_of<E>::value, is_vectorizable>(*this, tmp);
    } else {
      // 100% sure there's no overlap
      return utils::broadcast_copy < numpy_gexpr &, E, value,
             value - utils::dim_of<E>::value,
             is_vectorizable &&
                 std::is_same<dtype, typename dtype_of<E>::type>::value &&
                 is_vectorizable_array<E>::value > (*this, expr);
    }
  }

  template <class Arg, class... S>
  template <class E>
  typename std::enable_if<!may_overlap_gexpr<E>::value,
                          numpy_gexpr<Arg, S...> &>::type
  numpy_gexpr<Arg, S...>::_copy(E const &expr)
  {
    static_assert(value >= utils::dim_of<E>::value, "dimensions match");
    assert(buffer);
    return utils::broadcast_copy < numpy_gexpr &, E, value,
           value - utils::dim_of<E>::value,
           is_vectorizable &&
               std::is_same<dtype, typename dtype_of<E>::type>::value &&
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
  typename std::enable_if<!may_overlap_gexpr<E>::value,
                          numpy_gexpr<Arg, S...> &>::type
  numpy_gexpr<Arg, S...>::update_(E const &expr)
  {
    using BExpr =
        typename std::conditional<std::is_scalar<E>::value, broadcast<E, dtype>,
                                  E const &>::type;
    BExpr bexpr = expr;
    // 100% sure there's no overlap
    return utils::broadcast_update < Op, numpy_gexpr &, BExpr, value,
           value - (std::is_scalar<E>::value + utils::dim_of<E>::value),
           is_vectorizable &&
               types::is_vectorizable<typename std::remove_cv<
                   typename std::remove_reference<BExpr>::type>::type>::value &&
               std::is_same<dtype, typename dtype_of<typename std::decay<
                                       BExpr>::type>::type>::value >
                   (*this, bexpr);
  }

  template <class Arg, class... S>
  template <class Op, class E>
  typename std::enable_if<may_overlap_gexpr<E>::value,
                          numpy_gexpr<Arg, S...> &>::type
  numpy_gexpr<Arg, S...>::update_(E const &expr)
  {
    using BExpr =
        typename std::conditional<std::is_scalar<E>::value, broadcast<E, dtype>,
                                  E const &>::type;
    BExpr bexpr = expr;

    if (may_overlap(*this, expr)) {
      using NBExpr = ndarray<typename std::remove_reference<BExpr>::type::dtype,
                             std::remove_reference<BExpr>::type::value>;
      return utils::broadcast_update < Op, numpy_gexpr &, NBExpr, value,
             value - (std::is_scalar<E>::value + utils::dim_of<E>::value),
             is_vectorizable && types::is_vectorizable<E>::value &&
                 std::is_same<dtype,
                              typename std::decay<BExpr>::type::dtype>::value >
                     (*this, NBExpr(bexpr));
    } else {
      // 100% sure there's no overlap
      return utils::broadcast_update < Op, numpy_gexpr &, BExpr, value,
             value - (std::is_scalar<E>::value + utils::dim_of<E>::value),
             is_vectorizable && types::is_vectorizable<E>::value &&
                 std::is_same<dtype,
                              typename std::decay<BExpr>::type::dtype>::value >
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
  template <class E>
  numpy_gexpr<Arg, S...> &numpy_gexpr<Arg, S...>::operator|=(E const &expr)
  {
    return update_<pythonic::operator_::functor::ior>(expr);
  }

  template <class Arg, class... S>
  numpy_gexpr<Arg, S...> &numpy_gexpr<Arg, S...>::
  operator|=(numpy_gexpr<Arg, S...> const &expr)
  {
    return update_<pythonic::operator_::functor::ior>(expr);
  }

  template <class Arg, class... S>
  template <class E>
  numpy_gexpr<Arg, S...> &numpy_gexpr<Arg, S...>::operator&=(E const &expr)
  {
    return update_<pythonic::operator_::functor::iand>(expr);
  }

  template <class Arg, class... S>
  numpy_gexpr<Arg, S...> &numpy_gexpr<Arg, S...>::
  operator&=(numpy_gexpr<Arg, S...> const &expr)
  {
    return update_<pythonic::operator_::functor::iand>(expr);
  }

  template <class Arg, class... S>
  typename numpy_gexpr<Arg, S...>::const_iterator
  numpy_gexpr<Arg, S...>::begin() const
  {
    constexpr bool is_flat = is_strided || value != 1;
    return make_const_nditerator<is_flat>()(*this, 0);
  }

  template <class Arg, class... S>
  typename numpy_gexpr<Arg, S...>::const_iterator
  numpy_gexpr<Arg, S...>::end() const
  {
    return make_const_nditerator < is_strided ||
           value != 1 > ()(*this, _shape[0]);
  }

  template <class Arg, class... S>
  typename numpy_gexpr<Arg, S...>::iterator numpy_gexpr<Arg, S...>::begin()
  {
    constexpr bool is_flat = is_strided || value != 1;
    return make_nditerator<is_flat>()(*this, 0);
  }

  template <class Arg, class... S>
  typename numpy_gexpr<Arg, S...>::iterator numpy_gexpr<Arg, S...>::end()
  {
    return make_nditerator < is_strided || value != 1 > ()(*this, _shape[0]);
  }

  template <class Arg, class... S>
  auto numpy_gexpr<Arg, S...>::fast(long i) const
      -> decltype(std::declval<Arg>()[typename index_once<S...>::type()])
  {
    return arg[index_once<S...>::get(slices, i)];
  }

  template <class Arg, class... S>
  auto numpy_gexpr<Arg, S...>::fast(long i)
      -> decltype(std::declval<Arg>()[typename index_once<S...>::type()])
  {
    return arg[index_once<S...>::get(slices, i)];
  }

#ifdef USE_BOOST_SIMD
  template <class Arg, class... S>
  template <class vectorizer>
  typename numpy_gexpr<Arg, S...>::simd_iterator
      numpy_gexpr<Arg, S...>::vbegin(vectorizer) const
  {
    return {buffer + std::get<count_leading_long<S...>::value>(slices).lower};
  }

  template <class Arg, class... S>
  template <class vectorizer>
  typename numpy_gexpr<Arg, S...>::simd_iterator
      numpy_gexpr<Arg, S...>::vend(vectorizer) const
  {
    using vector_type = typename boost::simd::pack<dtype>;
    static const std::size_t vector_size = vector_type::static_size;
    return {buffer + std::get<count_leading_long<S...>::value>(slices).lower +
            long(_shape[0] / vector_size * vector_size)};
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
  template <size_t M>
  auto numpy_gexpr<Arg, S...>::fast(array<long, M> const &indices) const
      & -> decltype(nget<M - 1>().fast(*this, indices))
  {
    return nget<M - 1>().fast(*this, indices);
  }

  template <class Arg, class... S>
      template <size_t M>
      auto numpy_gexpr<Arg, S...>::fast(array<long, M> const &indices) &&
      -> decltype(nget<M - 1>().fast(std::move(*this), indices))
  {
    return nget<M - 1>().fast(std::move(*this), indices);
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
      auto numpy_gexpr<Arg, S...>::operator[](array<long, M> const &indices) &&
      -> decltype(nget<M - 1>()(std::move(*this), indices))
  {
    return nget<M - 1>()(std::move(*this), indices);
  }

  template <class Arg, class... S>
  template <class F>
  typename std::enable_if<is_numexpr_arg<F>::value &&
                              std::is_same<bool, typename F::dtype>::value,
                          numpy_fexpr<numpy_gexpr<Arg, S...>, F>>::type
  numpy_gexpr<Arg, S...>::fast(F const &filter) const
  {
    return numpy_fexpr<numpy_gexpr, F>(*this, filter);
  }

  template <class Arg, class... S>
  template <class F>
  typename std::enable_if<is_numexpr_arg<F>::value &&
                              std::is_same<bool, typename F::dtype>::value,
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
}
PYTHONIC_NS_END

#endif
