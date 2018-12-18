#ifndef PYTHONIC_NUMPY_ARGMINMAX_HPP
#define PYTHONIC_NUMPY_ARGMINMAX_HPP

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/numpy/asarray.hpp"
#include "pythonic/__builtin__/ValueError.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace details
  {
    template <class P, size_t... Is>
    P iota(utils::index_sequence<Is...>)
    {
      return {static_cast<typename P::value_type>(Is)...};
    }

    template <class P>
    P iota()
    {
      return iota<P>(utils::make_index_sequence<P::size>());
    }
  }
  template <class Op, class E, class T>
  long _argminmax_seq(E const &elts, T &minmax_elts)
  {
    long index = 0;
    long res = -1;
    for (auto const &elt : elts) {
      if (Op::value(elt, minmax_elts)) {
        minmax_elts = elt;
        res = index;
      }
      ++index;
    }

    return res;
  }
  template <class Op, class E, class T>
#ifdef USE_XSIMD
  typename std::enable_if<
      !E::is_vectorizable ||
          !types::is_vector_op<typename Op::op, T, T>::value ||
          std::is_same<typename E::dtype, bool>::value,
      long>::type
#else
  long
#endif
  _argminmax(E const &elts, T &minmax_elts, utils::int_<1>)
  {
    return _argminmax_seq<Op>(elts, minmax_elts);
  }

#ifdef USE_XSIMD
  template <bool IsInt>
  struct bool_caster;
  template <>
  struct bool_caster<true> {
    template <class T>
    auto operator()(T const &value) -> decltype(xsimd::bool_cast(value))
    {
      return xsimd::bool_cast(value);
    }
  };
  template <>
  struct bool_caster<false> {
    template <class T>
    T operator()(T const &value)
    {
      return value;
    }
  };

  template <class Op, class E, class T>
  typename std::enable_if<
      E::is_vectorizable && types::is_vector_op<typename Op::op, T, T>::value &&
          !std::is_same<typename E::dtype, bool>::value,
      long>::type
  _argminmax(E const &elts, T &minmax_elts, utils::int_<1>)
  {
    using vT = xsimd::simd_type<T>;
    using iT = xsimd::as_integer_t<T>;
    static const size_t vN = vT::size;
    const long n = elts.size();
    if (n >= std::numeric_limits<iT>::max()) {
      return _argminmax_seq<Op>(elts, minmax_elts);
    }

    auto viter = types::vectorizer_nobroadcast::vbegin(elts),
         vend = types::vectorizer_nobroadcast::vend(elts);

    const long bound = std::distance(viter, vend);
    long minmax_index = -1;
    if (bound > 0) {
      auto vacc = *viter;
      iT iota[vN] = {0};
      for (long i = 0; i < vN; ++i)
        iota[i] = i;
      auto curr = xsimd::load_unaligned(iota);
      xsimd::simd_type<iT> indices = curr;
      xsimd::simd_type<iT> step{vN};

      for (++viter; viter != vend; ++viter) {
        curr += step;
        auto c = *viter;
        vacc = typename Op::op{}(vacc, c);
        auto mask = c == vacc;
        indices =
            xsimd::select(bool_caster<std::is_floating_point<T>::value>{}(mask),
                          curr, indices);
      }

      alignas(sizeof(vT)) T stored[vN];
      vacc.store_aligned(&stored[0]);
      alignas(sizeof(vT)) long indexed[vN];
      indices.store_aligned(&indexed[0]);

      for (size_t j = 0; j < vN; ++j) {
        if (Op::value(stored[j], minmax_elts)) {
          minmax_elts = stored[j];
          minmax_index = indexed[j];
        }
      }
    }
    auto iter = elts.begin() + bound * vN;

    for (long i = bound * vN; i < n; ++i, ++iter) {
      if (Op::value(*iter, minmax_elts)) {
        minmax_elts = *iter;
        minmax_index = i;
      }
    }
    return minmax_index;
  }
#endif

  template <class Op, class E, size_t N, class T>
  long _argminmax(E const &elts, T &minmax_elts, utils::int_<N>)
  {
    long current_pos = 0;
    long current_minmaxarg = 0;
    for (auto &&elt : elts) {
      long v = _argminmax<Op>(elt, minmax_elts, utils::int_<N - 1>());
      if (v >= 0)
        current_minmaxarg = current_pos + v;
      current_pos += elt.flat_size();
    }
    return current_minmaxarg;
  }

  template <class Op, class E>
  long argminmax(E const &expr)
  {
    if (!expr.flat_size())
      throw types::ValueError("empty sequence");
    using elt_type = typename E::dtype;
    elt_type argminmax_value = Op::limit();
#ifndef USE_XSIMD
    if (utils::no_broadcast(expr))
      return _argminmax<Op>(types::make_fast_range(expr), argminmax_value,
                            utils::int_<E::value>());
    else
#endif
      return _argminmax<Op>(expr, argminmax_value, utils::int_<E::value>());
  }

  template <class Op, size_t Dim, size_t Axis, class T, class E, class V>
  void _argminmax_tail(T &out, E const &expr, long curr, V &curr_minmax,
                       std::integral_constant<size_t, 0>)
  {
    if (Op::value(expr, curr_minmax)) {
      out = curr;
      curr_minmax = expr;
    }
  }

  template <class Op, size_t Dim, size_t Axis, class T, class E, class V,
            size_t N>
  typename std::enable_if<Axis != (Dim - N), void>::type
  _argminmax_tail(T &&out, E const &expr, long curr, V &&curr_minmax,
                  std::integral_constant<size_t, N>)
  {
    static_assert(N >= 1, "specialization ok");
    for (long i = 0, n = std::get<0>(expr.shape()); i < n; ++i)
      _argminmax_tail<Op, Dim, Axis>(out.fast(i), expr.fast(i), curr,
                                     curr_minmax.fast(i),
                                     std::integral_constant<size_t, N - 1>());
  }

  template <class Op, size_t Dim, size_t Axis, class T, class E>
  typename std::enable_if<Axis == (Dim - 1), void>::type
  _argminmax_head(T &&out, E const &expr, std::integral_constant<size_t, 1>)
  {
    typename E::dtype val = Op::limit();
    for (long i = 0, n = std::get<0>(expr.shape()); i < n; ++i)
      _argminmax_tail<Op, Dim, Axis>(std::forward<T>(out), expr.fast(i), i, val,
                                     std::integral_constant<size_t, 0>());
  }

  template <class Op, size_t Dim, size_t Axis, class T, class E, size_t N>
  typename std::enable_if<Axis == (Dim - N), void>::type
  _argminmax_head(T &&out, E const &expr, std::integral_constant<size_t, N>)
  {
    static_assert(N > 1, "specialization ok");
    types::ndarray<typename E::dtype, types::array<long, N - 1>> val{
        out.shape(), Op::limit()};
    for (long i = 0, n = std::get<0>(expr.shape()); i < n; ++i)
      _argminmax_tail<Op, Dim, Axis>(std::forward<T>(out), expr.fast(i), i, val,
                                     std::integral_constant<size_t, N - 1>());
  }

  template <class Op, size_t Dim, size_t Axis, class T, class E, size_t N>
  typename std::enable_if<Axis != (Dim - N), void>::type
  _argminmax_head(T &&out, E const &expr, std::integral_constant<size_t, N>)
  {
    static_assert(N >= 1, "specialization ok");
    for (long i = 0, n = std::get<0>(expr.shape()); i < n; ++i)
      _argminmax_head<Op, Dim, Axis>(out.fast(i), expr.fast(i),
                                     std::integral_constant<size_t, N - 1>());
  }

  template <class Op, size_t N, class T, class E, size_t... Axis>
  void _argminmax_pick_axis(long axis, T &out, E const &expr,
                            utils::index_sequence<Axis...>)
  {
    std::initializer_list<bool>{
        ((Axis == axis) && (_argminmax_head<Op, N, Axis>(
                                out, expr, std::integral_constant<size_t, N>()),
                            true))...};
  }

  template <class Op, class E>
  types::ndarray<long, types::array<long, E::value - 1>>
  argminmax(E const &array, long axis)
  {
    if (axis < 0)
      axis += E::value;
    if (axis < 0 || size_t(axis) >= E::value)
      throw types::ValueError("axis out of bounds");
    auto shape = sutils::array(array.shape());
    types::array<long, E::value - 1> shp;
    auto next = std::copy(shape.begin(), shape.begin() + axis, shp.begin());
    std::copy(shape.begin() + axis + 1, shape.end(), next);
    types::ndarray<long, types::array<long, E::value - 1>> out{
        shp, __builtin__::None};
    typename E::dtype curr_minmax;
    _argminmax_pick_axis<Op, E::value>(axis, out, array,
                                       utils::make_index_sequence<E::value>());
    return out;
  }
}
PYTHONIC_NS_END

#endif
