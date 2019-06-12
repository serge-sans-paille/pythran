#ifndef PYTHONIC_TYPES_NUMPY_GEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_GEXPR_HPP

#include "pythonic/include/types/numpy_gexpr.hpp"

#include "pythonic/__builtin__/ValueError.hpp"

#include "pythonic/utils/meta.hpp"
#include "pythonic/operator_/iadd.hpp"
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
  template <class T, class pS, class Tp, class pSp, class... S, class... Sp>
  bool may_overlap(numpy_gexpr<ndarray<T, pS> const &, S...> const &gexpr,
                   numpy_gexpr<ndarray<Tp, pSp> const &, Sp...> const &expr)
  {
    if (!std::is_same<T, Tp>::value) {
      return false;
    }
    if (std::tuple_size<pS>::value != std::tuple_size<pSp>::value) {
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

  template <class T>
  T to_slice<T>::operator()(T value)
  {
    return value;
  }

  contiguous_slice to_slice<none_type>::operator()(none_type)
  {
    return {0, 1};
  }
  template <class T>
  T to_normalized_slice<T>::operator()(T value)
  {
    return value;
  }

  contiguous_normalized_slice to_normalized_slice<none_type>::
  operator()(none_type)
  {
    return {0, 1};
  }

  /* helper to build a new shape out of a shape and a slice with new axis
   */
  template <size_t N, class pS, class IsNewAxis>
  auto make_reshape(pS const &shape, IsNewAxis is_new_axis) -> decltype(
      sutils::copy_new_axis<std::tuple_size<pS>::value + N>(shape, is_new_axis))
  {
    return sutils::copy_new_axis<std::tuple_size<pS>::value + N>(shape,
                                                                 is_new_axis);
  }

  /* helper to build an extended slice aka numpy_gexpr out of a subscript
   */

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

    std::tuple<> merge_gexpr<std::tuple<>, std::tuple<>>::
    operator()(long const *, std::tuple<> const &t0, std::tuple<> const &)
    {
      return t0;
    }

    template <class... T0>
    std::tuple<T0...> merge_gexpr<std::tuple<T0...>, std::tuple<>>::
    operator()(long const *, std::tuple<T0...> const &t0, std::tuple<>)
    {
      return t0;
    }

    template <class T, size_t... Is>
    auto normalize_all(long const *s, T const &t, utils::index_sequence<Is...>)
        -> decltype(std::make_tuple(normalize(std::get<Is>(t), s[Is])...))
    {
      return std::make_tuple(normalize(std::get<Is>(t), s[Is])...);
    }

    template <class... T1>
    std::tuple<normalize_t<T1>...>
        merge_gexpr<std::tuple<>, std::tuple<T1...>>::
        operator()(long const *s, std::tuple<>, std::tuple<T1...> const &t1)
    {
      return normalize_all(s, t1, utils::make_index_sequence<sizeof...(T1)>());
    }

    template <class Arg, class... Sp>
    typename std::enable_if<count_new_axis<Sp...>::value == 0,
                            numpy_gexpr<Arg, Sp...>>::type
    _make_gexpr(Arg arg, std::tuple<Sp...> const &t)
    {
      return {arg, t};
    }

    template <class Arg, class S, size_t... Is>
    numpy_gexpr<Arg, typename to_normalized_slice<
                         typename std::tuple_element<Is, S>::type>::type...>
    _make_gexpr_helper(Arg arg, S const &s, utils::index_sequence<Is...>)
    {
      return {arg,
              to_normalized_slice<typename std::tuple_element<Is, S>::type>{}(
                  std::get<Is>(s))...};
    }

    template <class Arg, class... Sp>
    auto _make_gexpr(Arg arg, std::tuple<Sp...> const &s) ->
        typename std::enable_if<
            count_new_axis<Sp...>::value != 0,
            decltype(_make_gexpr_helper(
                arg.reshape(make_reshape<count_new_axis<Sp...>::value>(
                    arg.shape(), std::tuple<std::integral_constant<
                                     bool, to_slice<Sp>::is_new_axis>...>())),
                s, utils::make_index_sequence<sizeof...(Sp)>()))>::type
    {
      return _make_gexpr_helper(
          arg.reshape(make_reshape<count_new_axis<Sp...>::value>(
              arg.shape(), std::tuple<std::integral_constant<
                               bool, to_slice<Sp>::is_new_axis>...>())),
          s, utils::make_index_sequence<sizeof...(Sp)>());
    }

    template <class Arg, class... S>
    template <size_t... Is>
    numpy_gexpr<Arg, normalize_t<S>...> make_gexpr<Arg, S...>::
    operator()(Arg arg, std::tuple<S...> s, utils::index_sequence<Is...>)
    {
      return {arg, normalize(std::get<Is>(s), std::get<Is>(arg.shape()))...};
    }

    template <class Arg, class... S>
    numpy_gexpr<Arg, normalize_t<S>...> make_gexpr<Arg, S...>::
    operator()(Arg arg, S const &... s)
    {
      return operator()(arg, std::tuple<S...>(s...),
                        utils::make_index_sequence<sizeof...(S)>());
    }

    // this specialization is in charge of merging gexpr
    template <class Arg, class... S, class... Sp>
    auto make_gexpr<numpy_gexpr<Arg, S...> const &, Sp...>::
    operator()(numpy_gexpr<Arg, S...> const &arg, Sp const &... s) -> decltype(
        _make_gexpr(std::declval<Arg>(),
                    merge_gexpr<std::tuple<S...>, std::tuple<Sp...>>{}(
                        std::declval<long const *>(), std::tuple<S...>(),
                        std::tuple<Sp...>())))
    {
      auto const shp = sutils::array(arg.shape());
      return _make_gexpr(arg.arg,
                         merge_gexpr<std::tuple<S...>, std::tuple<Sp...>>{}(
                             shp.data(), arg.slices, std::make_tuple(s...)));
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
  typename std::enable_if<
      std::is_same<Slice, normalized_slice>::value ||
          std::is_same<Slice, contiguous_normalized_slice>::value,
      void>::type
  numpy_gexpr<Arg, S...>::init_shape(Slice const &s, utils::int_<1>,
                                     utils::int_<J>)
  {
    sutils::assign(std::get<J>(_shape),
                   std::get<sizeof...(S)-1>(slices).size());
  }

  template <class Arg, class... S>
  template <size_t I, size_t J, class Slice>
  typename std::enable_if<
      std::is_same<Slice, normalized_slice>::value ||
          std::is_same<Slice, contiguous_normalized_slice>::value,
      void>::type
  numpy_gexpr<Arg, S...>::init_shape(Slice const &s, utils::int_<I>,
                                     utils::int_<J>)
  {
    sutils::assign(std::get<J>(_shape),
                   std::get<sizeof...(S)-I>(slices).size());
    init_shape(std::get<sizeof...(S)-I + 1>(slices), utils::int_<I - 1>(),
               utils::int_<J + 1>());
  }

  template <class Arg, class... S>
  template <size_t J>
  void numpy_gexpr<Arg, S...>::init_shape(long cs, utils::int_<1>,
                                          utils::int_<J>)
  {
    assert(cs >= 0 && "normalized");
  }

  template <class Arg, class... S>
  template <size_t I, size_t J>
  void numpy_gexpr<Arg, S...>::init_shape(long cs, utils::int_<I>,
                                          utils::int_<J>)
  {
    assert(cs >= 0 && "normalized");
    init_shape(std::get<sizeof...(S)-I + 1>(slices), utils::int_<I - 1>(),
               utils::int_<J>());
  }

  template <class Arg, class... S>
  numpy_gexpr<Arg, S...>::numpy_gexpr(Arg const &arg,
                                      std::tuple<S const &...> const &values)
      : arg(arg), slices(values), buffer(const_cast<dtype *>(this->arg.buffer))
  {
    init_shape(std::get<0>(slices), utils::int_<sizeof...(S)>(),
               utils::int_<0>());
    buffer += buffer_offset(
        arg, std::get<count_leading_long<S...>::value>(slices).lower);

    sutils::copy_shape<sizeof...(S)-count_long<S...>::value,
                       count_long<S...>::value>(
        _shape, arg.shape(),
        utils::make_index_sequence<value -
                                   (sizeof...(S)-count_long<S...>::value)>());
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
    buffer += buffer_offset(
        arg, std::get<count_leading_long<S...>::value>(slices).lower);
    sutils::copy_shape<0, 1>(_shape, expr.shape(),
                             utils::make_index_sequence<value>());
  }

  template <class Arg, class... S>
  template <class G>
  numpy_gexpr<Arg, S...>::numpy_gexpr(G const &expr, Arg &&arg)
      : arg(std::forward<Arg>(arg)), slices(tuple_pop(expr.slices)),
        buffer(arg.buffer)
  {
    buffer += buffer_offset(
        arg, std::get<count_leading_long<S...>::value>(slices).lower);
    sutils::copy_shape<0, 1>(_shape, expr.shape(),
                             utils::make_index_sequence<value>());
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
    assert(buffer);
    if (may_overlap(*this, expr)) {
      return utils::broadcast_copy<
          numpy_gexpr &, ndarray<typename E::dtype, typename E::shape_t>, value,
          value - utils::dim_of<E>::value, is_vectorizable>(
          *this, ndarray<typename E::dtype, typename E::shape_t>(expr));
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
    if (buffer == nullptr) {
      // arg = expr.arg;
      const_cast<typename std::decay<Arg>::type &>(arg) = expr.arg;
      slices = expr.slices;
      buffer = arg.buffer;
      _shape = expr.shape();
      return *this;
    } else {
      return _copy(expr);
    }
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
      using NBExpr =
          ndarray<typename std::remove_reference<BExpr>::type::dtype,
                  typename std::remove_reference<BExpr>::type::shape_t>;
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
  template <class E>
  numpy_gexpr<Arg, S...> &numpy_gexpr<Arg, S...>::operator^=(E const &expr)
  {
    return update_<pythonic::operator_::functor::ixor>(expr);
  }

  template <class Arg, class... S>
  numpy_gexpr<Arg, S...> &numpy_gexpr<Arg, S...>::
  operator^=(numpy_gexpr<Arg, S...> const &expr)
  {
    return update_<pythonic::operator_::functor::ixor>(expr);
  }

  template <class Arg, class... S>
  typename numpy_gexpr<Arg, S...>::const_iterator
  numpy_gexpr<Arg, S...>::begin() const
  {
    return make_const_nditerator < is_strided || value != 1 > ()(*this, 0);
  }

  template <class Arg, class... S>
  typename numpy_gexpr<Arg, S...>::const_iterator
  numpy_gexpr<Arg, S...>::end() const
  {
    return make_const_nditerator < is_strided || value != 1 > ()(*this, size());
  }

  template <class Arg, class... S>
  typename numpy_gexpr<Arg, S...>::iterator numpy_gexpr<Arg, S...>::begin()
  {
    return make_nditerator < is_strided || value != 1 > ()(*this, 0);
  }

  template <class Arg, class... S>
  typename numpy_gexpr<Arg, S...>::iterator numpy_gexpr<Arg, S...>::end()
  {
    return make_nditerator < is_strided || value != 1 > ()(*this, size());
  }

  template <class Arg, class... S>
  auto numpy_gexpr<Arg, S...>::fast(long i) const
      -> decltype(numpy_gexpr_helper<Arg, S...>::get(*this, i))
  {
    return numpy_gexpr_helper<Arg, S...>::get(
        *this,
        (is_contiguous<S...>::value
             ? i
             : std::get<count_leading_long<S...>::value>(slices).step * i));
  }

  template <class Arg, class... S>
  auto numpy_gexpr<Arg, S...>::fast(long i)
      -> decltype(numpy_gexpr_helper<Arg, S...>::get(*this, i))
  {
    return numpy_gexpr_helper<Arg, S...>::get(
        *this,
        (is_contiguous<S...>::value
             ? i
             : std::get<count_leading_long<S...>::value>(slices).step * i));
  }

#ifdef USE_XSIMD
  template <class Arg, class... S>
  template <class vectorizer>
  typename numpy_gexpr<Arg, S...>::simd_iterator
      numpy_gexpr<Arg, S...>::vbegin(vectorizer) const
  {
    return {buffer};
  }

  template <class Arg, class... S>
  template <class vectorizer>
  typename numpy_gexpr<Arg, S...>::simd_iterator
      numpy_gexpr<Arg, S...>::vend(vectorizer) const
  {
    using vector_type = typename xsimd::simd_type<dtype>;
    static const std::size_t vector_size = vector_type::size;
    return {buffer + long(size() / vector_size * vector_size)};
  }

#endif

  template <class Arg, class... S>
  auto numpy_gexpr<Arg, S...>::operator[](long i) const
      -> decltype(this->fast(i))
  {
    if (i < 0)
      i += std::get<0>(_shape);
    return fast(i);
  }

  template <class Arg, class... S>
  auto numpy_gexpr<Arg, S...>::operator[](long i) -> decltype(this->fast(i))
  {
    if (i < 0)
      i += std::get<0>(_shape);
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
  template <class... Sp>
  auto numpy_gexpr<Arg, S...>::operator()(long i, Sp const &... s) const
      -> decltype(std::declval<value_type>()(s...))
  {
    return (*this)[i](s...);
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
  typename std::enable_if<
      is_numexpr_arg<F>::value && std::is_same<bool, typename F::dtype>::value,
      numpy_vexpr<numpy_gexpr<Arg, S...>, ndarray<long, pshape<long>>>>::type
  numpy_gexpr<Arg, S...>::fast(F const &filter) const
  {
    long sz = std::get<0>(filter.shape());
    long *raw = (long *)malloc(sz * sizeof(long));
    long n = 0;
    for (long i = 0; i < sz; ++i)
      if (filter.fast(i))
        raw[n++] = i;
    // realloc(raw, n * sizeof(long));
    long shp[1] = {n};
    return this->fast(
        ndarray<long, pshape<long>>(raw, shp, types::ownership::owned));
  }

  template <class Arg, class... S>
  template <class F>
  typename std::enable_if<
      is_numexpr_arg<F>::value && std::is_same<bool, typename F::dtype>::value,
      numpy_vexpr<numpy_gexpr<Arg, S...>, ndarray<long, pshape<long>>>>::type
      numpy_gexpr<Arg, S...>::
      operator[](F const &filter) const
  {
    return fast(filter);
  }

  template <class Arg, class... S>
  numpy_gexpr<Arg, S...>::operator bool() const
  {
    if (sutils::any_of(_shape, [](long n) { return n != 1; }))
      throw ValueError("The truth value of an array with more than one element "
                       "is ambiguous. Use a.any() or a.all()");
    return *buffer;
  }

  template <class Arg, class... S>
  long numpy_gexpr<Arg, S...>::flat_size() const
  {
    return sutils::prod(_shape);
  }

  template <class Arg, class... S>
  long numpy_gexpr<Arg, S...>::size() const
  {
    return std::get<0>(_shape);
  }

  // As gexpr has to begin with a slice. When we access it, we need to forward
  // the firsts accessed information
  // to an iexpr until the value in S... is a slice again.
  template <class Arg, class S0, class S1, class... S>
  typename numpy_gexpr_helper<Arg, S0, S1, S...>::type
  numpy_gexpr_helper<Arg, S0, S1, S...>::get(
      numpy_gexpr<Arg, S0, S1, S...> const &e, long i)
  {
    return type(e, numpy_iexpr<Arg const &>(e.arg, i, e.buffer));
  }

  template <class Arg, class S0, class S1, class... S>
  typename numpy_gexpr_helper<Arg, S0, S1, S...>::type
  numpy_gexpr_helper<Arg, S0, S1, S...>::get(numpy_gexpr<Arg, S0, S1, S...> &e,
                                             long i)
  {
    return type(e, numpy_iexpr<Arg const &>(e.arg, i, e.buffer));
  }

  // Compute forwarding of "long" index to iexpr until we reach a new slice in
  // S... parameters
  namespace
  {

    // We reach a new slice so we have a new gexpr
    template <size_t N, class Arg, class... S>
    template <class E, class F>
    typename finalize_numpy_gexpr_helper<N, Arg, contiguous_normalized_slice,
                                         S...>::type
    finalize_numpy_gexpr_helper<N, Arg, contiguous_normalized_slice, S...>::get(
        E const &e, F &&f)
    {
      return {e, std::forward<F>(f)};
    }

    // We reach a new slice so we have a new gexpr
    template <size_t N, class Arg, class... S>
    template <class E, class F>
    typename finalize_numpy_gexpr_helper<N, Arg, normalized_slice, S...>::type
    finalize_numpy_gexpr_helper<N, Arg, normalized_slice, S...>::get(E const &e,
                                                                     F &&f)
    {
      return type(e, std::forward<F>(f));
    }

    // We have a long index so it is ! a gexpr but a iexpr.
    // We declare a new iexpr && we continue looking for a new slice.
    template <size_t N, class Arg, class... S>
    template <class E, class F>
    auto finalize_numpy_gexpr_helper<N, Arg, long, S...>::get(E const &e, F &&f)
        -> decltype(finalize_numpy_gexpr_helper<
            N + 1, numpy_iexpr<Arg const &>,
            S...>::get(e, std::declval<numpy_iexpr<Arg const &>>()))
    {
      return finalize_numpy_gexpr_helper<N + 1, numpy_iexpr<Arg const &>,
                                         S...>::get(e,
                                                    numpy_iexpr<Arg const &>(
                                                        std::forward<F>(f),
                                                        std::get<N + 1>(
                                                            e.slices)));
    }

    template <size_t N, class Arg, class... S>
    template <class E, class F>
    auto finalize_numpy_gexpr_helper<N, Arg, long, S...>::get(E &e, F &&f)
        -> decltype(finalize_numpy_gexpr_helper<
            N + 1, numpy_iexpr<Arg const &>,
            S...>::get(e, std::declval<numpy_iexpr<Arg const &> &>()))
    {
      numpy_iexpr<Arg const &> iexpr(std::forward<F>(f),
                                     std::get<N + 1>(e.slices));
      return finalize_numpy_gexpr_helper<N + 1, numpy_iexpr<Arg const &>,
                                         S...>::get(e, iexpr);
    }

    // If it was a single sliced array, we can return the matching iexpr.
    template <size_t N, class Arg>
    template <class E, class F>
    auto finalize_numpy_gexpr_helper<N, Arg, long>::get(E const &e, F const &f)
        -> decltype(numpy_iexpr_helper<F, Arg::value>::get(f, 0))
    {
      return numpy_iexpr_helper<F, Arg::value>::get(f,
                                                    std::get<N + 1>(e.slices));
    }

    template <size_t N, class Arg>
    template <class E, class F>
    auto finalize_numpy_gexpr_helper<N, Arg, long>::get(E const &e, F &f)
        -> decltype(numpy_iexpr_helper<F, Arg::value>::get(f, 0))
    {
      return numpy_iexpr_helper<F, Arg::value>::get(f,
                                                    std::get<N + 1>(e.slices));
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
                                                      e.arg, i, e.buffer));
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
                                                      e.arg, i, e.buffer));
  }

  // If we have no more slice later, we can say it is an iexpr (We look only
  // for one last long? Not many last long?)
  template <class Arg, class S>
  auto numpy_gexpr_helper<Arg, S, long>::get(numpy_gexpr<Arg, S, long> const &e,
                                             long i)
      -> decltype(numpy_iexpr_helper<numpy_iexpr<Arg const &>,
                                     numpy_iexpr<Arg const &>::value>::
                      get(std::declval<numpy_iexpr<Arg const &>>(), 0))
  {
    return numpy_iexpr_helper<numpy_iexpr<Arg const &>,
                              numpy_iexpr<Arg const &>::value>::
        get(numpy_iexpr<Arg const &>(e.arg, i, e.buffer),
            std::get<1>(e.slices));
  }

  template <class Arg, class S>
  auto numpy_gexpr_helper<Arg, S, long>::get(numpy_gexpr<Arg, S, long> &e,
                                             long i)
      -> decltype(numpy_iexpr_helper<numpy_iexpr<Arg const &>,
                                     numpy_iexpr<Arg const &>::value>::
                      get(std::declval<numpy_iexpr<Arg const &> &>(), 0))
  {
    numpy_iexpr<Arg const &> iexpr(e.arg, i, e.buffer);
    return numpy_iexpr_helper<
        numpy_iexpr<Arg const &>,
        numpy_iexpr<Arg const &>::value>::get(iexpr, std::get<1>(e.slices));
  }
}
PYTHONIC_NS_END

#endif
