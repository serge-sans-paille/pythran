#ifndef PYTHONIC_INCLUDE_TYPES_NUMPY_GEXPR_HPP
#define PYTHONIC_INCLUDE_TYPES_NUMPY_GEXPR_HPP

#include "pythonic/include/utils/meta.hpp"
#include "pythonic/include/utils/array_helper.hpp"

PYTHONIC_NS_BEGIN

namespace types
{

  template <class... S>
  struct index_once;

  template <class... S>
  struct index_once<slice, S...> {
    using type = std::tuple<long, S...>;
    static type get(std::tuple<slice, S...> const &s, long i)
    {
      return std::tuple_cat(
          std::tuple<long>(i * std::get<0>(s).step + std::get<0>(s).lower),
          tuple_tail(s));
    }
  };

  template <class... S>
  struct index_once<contiguous_slice, S...> {
    using type = std::tuple<long, S...>;
    static type get(std::tuple<contiguous_slice, S...> const &s, long i)
    {
      return std::tuple_cat(std::tuple<long>(i + std::get<0>(s).lower),
                            tuple_tail(s));
    }
  };

  template <class... S>
  struct index_once<long, S...> {
    using type = decltype(
        std::tuple_cat(std::tuple<long>(), typename index_once<S...>::type()));

    static type get(std::tuple<long, S...> const &s, long i)
    {
      return std::tuple_cat(std::tuple<long>(std::get<0>(s)),
                            index_once<S...>::get(tuple_tail(s), i));
    }
  };
  template <>
  struct index_once<> {
    using type = std::tuple<long>;
    static type get(std::tuple<> const &s, long i)
    {
      return {i};
    }
  };

  /* helper to count new axis
   */
  template <class... T>
  struct count_new_axis;

  template <>
  struct count_new_axis<types::none_type> {
    static constexpr size_t value = 1;
  };

  template <class T>
  struct count_new_axis<T> {
    static constexpr size_t value = 0;
  };

  template <class T0, class... T>
  struct count_new_axis<T0, T...> {
    static constexpr size_t value =
        count_new_axis<T0>::value + count_new_axis<T...>::value;
  };

  /* helper to turn a new axis into a slice
   */
  template <class T>
  struct to_slice {
    using type = T;
    static constexpr bool is_new_axis = false;
    T operator()(T value);
  };

  template <>
  struct to_slice<none_type> {
    using type = contiguous_slice;
    static constexpr bool is_new_axis = true;
    contiguous_slice operator()(none_type);
  };

  /* helper to build a new shape out of a shape && a slice with new axis
   */
  template <size_t N, size_t M, size_t C>
  array<long, N> make_reshape(array<long, M> const &shape,
                              array<bool, C> const &is_new_axis);

  /* helper to build an extended slice aka numpy_gexpr out of a subscript
   */
  template <size_t C, bool Final>
  struct extended_slice {
    template <class T, size_t N, class... S>
    auto operator()(ndarray<T, N> &&a, S const &... s)
        -> decltype(std::declval<ndarray<T, N + C>>()(
            std::declval<typename to_slice<S>::type>()...));

    template <class T, size_t N, class... S>
    auto operator()(ndarray<T, N> const &a, S const &... s)
        -> decltype(std::declval<ndarray<T, N + C>>()(
            std::declval<typename to_slice<S>::type>()...));
  };

  template <>
  struct extended_slice<0, false> {

    template <class T, size_t N, class... S>
    numpy_gexpr<ndarray<T, N>, S...> operator()(ndarray<T, N> &&a,
                                                S const &... s)
    {
      return {std::move(a), s...};
    }

    template <class T, size_t N, class... S>
    numpy_gexpr<ndarray<T, N> const &, S...> operator()(ndarray<T, N> const &a,
                                                        S const &... s)
    {
      return {a, s...};
    }
  };

  template <>
  struct extended_slice<0, true> {

    template <class T, size_t N, class... S>
    typename std::enable_if<
        utils::all_of<std::is_same<S, long>::value...>::value, T &>::type
    operator()(ndarray<T, N> const &a, S const &... s)
    {
      return const_cast<ndarray<T, N> &>(a)[array<long, N>{{s...}}];
    }
    template <class T, size_t N, class... S>
    typename std::enable_if<
        !utils::all_of<std::is_same<S, long>::value...>::value,
        numpy_gexpr<ndarray<T, N>, S...>>::type
    operator()(ndarray<T, N> const &a, S const &... s)
    {
      return {a, s...};
    }
  };

  /* manually unrolled copy function
   */
  template <size_t I>
  struct flat_copy;

  template <>
  struct flat_copy<0> {
    void operator()(long *, long const *);
  };

  template <size_t I>
  struct flat_copy {
    void operator()(long *to, long const *from);
  };

  /* Meta-Function to count the number of slices in a type list
   */
  template <class... Types>
  struct count_long;

  template <>
  struct count_long<long> {
    static constexpr size_t value = 1;
  };

  template <>
  struct count_long<slice> {
    static constexpr size_t value = 0;
  };

  template <>
  struct count_long<contiguous_slice> {
    static constexpr size_t value = 0;
  };

  template <class T, class... Types>
  struct count_long<T, Types...> {
    static_assert(!std::is_same<T, none_type>::value,
                  "none-type should have been pruned");
    static constexpr size_t value =
        count_long<T>::value + count_long<Types...>::value;
  };

  template <>
  struct count_long<> {
    static constexpr size_t value = 0;
  };

  /* helper to get the type of the nth element of an array
   */
  template <class T, size_t N>
  struct nth_value_type {
    using type = typename nth_value_type<typename T::value_type, N - 1>::type;
  };

  template <class T>
  struct nth_value_type<T, 0> {
    using type = T;
  };

  /* helper that yields true if the first slice of a pack is a contiguous
   * slice
   */
  template <class... S>
  struct is_contiguous {
    static const bool value = false;
  };

  template <class... S>
  struct is_contiguous<contiguous_slice, S...> {
    static const bool value = true;
  };

  /* numpy_gexpr factory
   *
   * replaces the constructor, in order to properly merge gexpr composition
   *into a single gexpr
   */
  namespace details
  {

    // this struct is specialized for every type combination && takes care of
    // the slice merge
    template <class T, class Tp>
    struct merge_gexpr;

    template <>
    struct merge_gexpr<std::tuple<>, std::tuple<>> {
      std::tuple<> const &operator()(std::tuple<> const &t0,
                                     std::tuple<> const &);
    };

    template <class... T0>
    struct merge_gexpr<std::tuple<T0...>, std::tuple<>> {
      std::tuple<T0...> const &operator()(std::tuple<T0...> const &t0,
                                          std::tuple<>);
    };

    template <class... T1>
    struct merge_gexpr<std::tuple<>, std::tuple<T1...>> {
      std::tuple<T1...> const &operator()(std::tuple<>,
                                          std::tuple<T1...> const &t1);
    };

    template <class S0, class... T0, class S1, class... T1>
    struct merge_gexpr<std::tuple<S0, T0...>, std::tuple<S1, T1...>> {
      auto operator()(std::tuple<S0, T0...> const &t0,
                      std::tuple<S1, T1...> const &t1)
          -> decltype(std::tuple_cat(
              std::make_tuple(std::get<0>(t0) * std::get<0>(t1)),
              merge_gexpr<std::tuple<T0...>, std::tuple<T1...>>{}(
                  tuple_tail(t0), tuple_tail(t1))));
    };

    template <class... T0, class S1, class... T1>
    struct merge_gexpr<std::tuple<long, T0...>, std::tuple<S1, T1...>> {
      auto operator()(std::tuple<long, T0...> const &t0,
                      std::tuple<S1, T1...> const &t1)
          -> decltype(std::tuple_cat(
              std::make_tuple(std::get<0>(t0)),
              merge_gexpr<std::tuple<T0...>, std::tuple<S1, T1...>>{}(
                  tuple_tail(t0), t1)));
    };

    template <class S0, class... T0, class... T1>
    struct merge_gexpr<std::tuple<S0, T0...>, std::tuple<long, T1...>> {
      auto operator()(std::tuple<S0, T0...> const &t0,
                      std::tuple<long, T1...> const &t1)
          -> decltype(std::tuple_cat(
              std::make_tuple(std::get<0>(t1) * std::get<0>(t0).step +
                              std::get<0>(t0).lower),
              merge_gexpr<std::tuple<T0...>, std::tuple<T1...>>{}(
                  tuple_tail(t0), tuple_tail(t1))));
    };

    template <class... T0, class... T1>
    struct merge_gexpr<std::tuple<long, T0...>, std::tuple<long, T1...>> {
      auto operator()(std::tuple<long, T0...> const &t0,
                      std::tuple<long, T1...> const &t1)
          -> decltype(std::tuple_cat(
              std::make_tuple(std::get<0>(t0)),
              merge_gexpr<std::tuple<T0...>, std::tuple<long, T1...>>{}(
                  tuple_tail(t0), t1)));
    };

    template <class Arg, class... S>
    struct make_gexpr {
      numpy_gexpr<Arg, S...> operator()(Arg arg, S const &... s);
    };

    // this specialization is in charge of merging gexpr
    template <class Arg, class... S, class... Sp>
    struct make_gexpr<numpy_gexpr<Arg, S...> const &, Sp...> {
      auto operator()(numpy_gexpr<Arg, S...> const &arg, Sp const &... s)
          -> decltype(std::declval<
              Arg>()[merge_gexpr<std::tuple<S...>, std::tuple<Sp...>>{}(
              std::tuple<S...>(), std::tuple<Sp...>())]);
    };
  }

  template <class Arg, class... S>
  auto make_gexpr(Arg &&arg, S const &... s)
      -> decltype(details::make_gexpr<Arg, S...>{}(std::forward<Arg>(arg),
                                                   s...));

  /* type-based compile time overlapping detection: detect if a type may
   *overlap with another
   * the goal is to detect whether the following operation
   *
   * a[...] = b
   *
   * requires a copy.
   *
   * It requires a copy if b = a[...], as in
   *
   * a[1:] = a[:-1]
   *
   * because this is *!* equivalent to for i in range(0, n-1): a[i+1] = a[i]
   *
   * to avoid the copy, we rely on the lhs type
   */

  template <class E>
  struct may_overlap_gexpr : std::integral_constant<bool, !is_dtype<E>::value> {
  };

  template <class T0, class T1>
  struct may_overlap_gexpr<broadcast<T0, T1>> : std::false_type {
  };

  template <class E>
  struct may_overlap_gexpr<broadcasted<E>> : std::false_type {
  };

  template <class E>
  struct may_overlap_gexpr<E &> : may_overlap_gexpr<E> {
  };

  template <class E>
  struct may_overlap_gexpr<E const &> : may_overlap_gexpr<E> {
  };

  template <class T, size_t N>
  struct may_overlap_gexpr<ndarray<T, N>> : std::false_type {
  };

  template <class E>
  struct may_overlap_gexpr<numpy_texpr<E>> : may_overlap_gexpr<E> {
  };

  template <class E, class... S>
  struct may_overlap_gexpr<numpy_gexpr<E, S...>>
      : utils::any_of<
            !std::is_same<typename std::decay<S>::type, long>::value...> {
  };

  template <class E>
  struct may_overlap_gexpr<list<E>>
      : std::integral_constant<bool, !is_dtype<E>::value> {
  };

  template <class E, size_t N>
  struct may_overlap_gexpr<array<E, N>> : may_overlap_gexpr<E> {
  };

  template <class Op, class... Args>
  struct may_overlap_gexpr<numpy_expr<Op, Args...>>
      : utils::any_of<may_overlap_gexpr<Args>::value...> {
  };

  /* Expression template for numpy expressions - extended slicing operators
   */
  template <class Arg, class... S>
  struct numpy_gexpr {
    // numpy_gexpr is a wrapper for extended sliced array around a numpy
    // expression.
    // It contains compacted sorted slices value in lower, step && upper is
    // the same as shape.
    // indices for long index are store in the indices array.
    // position for slice && long value in the extended slice can be found
    // through the S... template
    // && compacted values as we know that first S is a slice.

    using dtype = typename std::remove_reference<Arg>::type::dtype;
    static constexpr size_t value =
        std::remove_reference<Arg>::type::value - count_long<S...>::value;

    // It is ! possible to vectorize everything. We only vectorize if the
    // last dimension is contiguous, which happens if
    // 1. Arg is an ndarray (this is too strict)
    // 2. the size of the gexpr is lower than the dim of arg, || it's the
    // same, but the last slice is contiguous
    static const bool is_vectorizable =
        std::remove_reference<Arg>::type::is_vectorizable &&
        (sizeof...(S) < std::remove_reference<Arg>::type::value ||
         std::is_same<contiguous_slice,
                      typename std::tuple_element<
                          sizeof...(S)-1, std::tuple<S...>>::type>::value);
    static const bool is_strided =
        std::remove_reference<Arg>::type::is_strided ||
        (((sizeof...(S)-count_long<S...>::value) == value) &&
         !std::is_same<contiguous_slice,
                       typename std::tuple_element<
                           sizeof...(S)-1, std::tuple<S...>>::type>::value);

    using value_type =
        decltype(std::declval<Arg>()[typename index_once<S...>::type()]);

    using iterator =
        typename std::conditional<is_strided || value != 1,
                                  nditerator<numpy_gexpr>, dtype *>::type;
    using const_iterator =
        typename std::conditional<is_strided || value != 1,
                                  const_nditerator<numpy_gexpr>,
                                  dtype const *>::type;

#ifdef CYTHON_ABI
    typename std::remove_reference<Arg>::type arg;
#else
    Arg arg;
#endif
    std::tuple<S...> slices;
    dtype *buffer;
    array<long, value> _shape;
    array<long, value> const &shape() const
    {
      return _shape;
    }

    numpy_gexpr();
    numpy_gexpr(numpy_gexpr const &) = default;
    numpy_gexpr(numpy_gexpr &&) = default;

    template <class Argp> // ! using the default one, to make it possible to
    // accept reference && non reference version of
    // Argp
    numpy_gexpr(numpy_gexpr<Argp, S...> const &other);

    template <size_t J, class Slice>
    typename std::enable_if<std::is_same<Slice, slice>::value ||
                                std::is_same<Slice, contiguous_slice>::value,
                            void>::type
    init_shape(Slice const &s, utils::int_<1>, utils::int_<J>);

    template <size_t I, size_t J, class Slice>
    typename std::enable_if<std::is_same<Slice, slice>::value ||
                                std::is_same<Slice, contiguous_slice>::value,
                            void>::type
    init_shape(Slice const &s, utils::int_<I>, utils::int_<J>);

    template <size_t J>
    void init_shape(long cs, utils::int_<1>, utils::int_<J>);

    template <size_t I, size_t J>
    void init_shape(long cs, utils::int_<I>, utils::int_<J>);

    // private because we must use the make_gexpr factory to create a gexpr
  public:
    template <class _Arg, class... _S>
    friend struct details::make_gexpr;

    template <size_t C, bool Final>
    friend struct extended_slice;

#ifdef ENABLE_PYTHON_MODULE
    template <typename T>
    friend struct pythonic::from_python;
#endif

    // When we create a new numpy_gexpr, we deduce step, lower && shape from
    // slices
    // && indices from long value.
    // Also, last shape information are set from origin array like in :
    // >>> a = numpy.arange(2*3*4).reshape(2,3,4)
    // >>> a[:, 1]
    // the last dimension (4) is missing from slice information
    // Finally, if origin expression was already sliced, lower bound && step
    // have to
    // be increased
    numpy_gexpr(Arg const &arg, std::tuple<S const &...> const &values);
    numpy_gexpr(Arg const &arg, S const &... s);

  public:
    template <class E>
    typename std::enable_if<may_overlap_gexpr<E>::value, numpy_gexpr &>::type
    _copy(E const &expr);

    template <class E>
    typename std::enable_if<!may_overlap_gexpr<E>::value, numpy_gexpr &>::type
    _copy(E const &expr);

    template <class E>
    numpy_gexpr &operator=(E const &expr);

    numpy_gexpr &operator=(numpy_gexpr const &expr);

    template <class Op, class E>
    typename std::enable_if<may_overlap_gexpr<E>::value, numpy_gexpr &>::type
    update_(E const &expr);

    template <class Op, class E>
    typename std::enable_if<!may_overlap_gexpr<E>::value, numpy_gexpr &>::type
    update_(E const &expr);

    template <class E>
    numpy_gexpr &operator+=(E const &expr);

    numpy_gexpr &operator+=(numpy_gexpr const &expr);

    template <class E>
    numpy_gexpr &operator-=(E const &expr);

    numpy_gexpr &operator-=(numpy_gexpr const &expr);

    template <class E>
    numpy_gexpr &operator*=(E const &expr);

    numpy_gexpr &operator*=(numpy_gexpr const &expr);

    template <class E>
    numpy_gexpr &operator/=(E const &expr);

    numpy_gexpr &operator/=(numpy_gexpr const &expr);

    template <class E>
    numpy_gexpr &operator|=(E const &expr);

    numpy_gexpr &operator|=(numpy_gexpr const &expr);

    template <class E>
    numpy_gexpr &operator&=(E const &expr);

    numpy_gexpr &operator&=(numpy_gexpr const &expr);

    const_iterator begin() const;
    const_iterator end() const;

    iterator begin();
    iterator end();

    auto fast(long i) const
        -> decltype(std::declval<Arg>()[typename index_once<S...>::type()]);

    auto fast(long i)
        -> decltype(std::declval<Arg>()[typename index_once<S...>::type()]);

#ifdef USE_BOOST_SIMD
    using simd_iterator = const_simd_nditerator<numpy_gexpr>;
    using simd_iterator_nobroadcast = simd_iterator;
    template <class vectorizer>
    simd_iterator vbegin(vectorizer) const;
    template <class vectorizer>
    simd_iterator vend(vectorizer) const;
#endif

    template <class... Sp>
    auto operator()(contiguous_slice const &s0, Sp const &... s) const
        -> decltype(make_gexpr(*this, s0, s...));

    auto operator[](contiguous_slice const &s0) const
        -> decltype(make_gexpr(*this, s0));

    template <class... Sp>
    auto operator()(slice const &s0, Sp const &... s) const
        -> decltype(make_gexpr(*this, s0, s...));

    auto operator[](slice const &s0) const -> decltype(make_gexpr(*this, s0));

    template <class Sp, size_t... Is>
    auto _index(Sp const &s, utils::index_sequence<Is...>) const
        -> decltype((*this)(std::get<Is>(s)...))
    {
      return (*this)(std::get<Is>(s)...);
    }

    template <class... Sp>
    auto operator[](std::tuple<Sp...> const &s) const
        -> decltype(this->_index(s,
                                 utils::make_index_sequence<sizeof...(Sp)>()))
    {
      return this->_index(s, utils::make_index_sequence<sizeof...(Sp)>());
    }

    template <class... Sp>
    auto operator()(long i, Sp const &... s) const
        -> decltype(make_gexpr(*this, i, s...))
    {
      return make_gexpr(*this, i, s...);
    }

    template <size_t M>
    auto fast(array<long, M> const &indices) const
        & -> decltype(nget<M - 1>().fast(*this, indices));

    template <size_t M>
        auto fast(array<long, M> const &indices) &&
        -> decltype(nget<M - 1>().fast(std::move(*this), indices));

    template <size_t M>
    auto operator[](array<long, M> const &indices) const
        & -> decltype(nget<M - 1>()(*this, indices));

    template <size_t M>
        auto operator[](array<long, M> const &indices) &&
        -> decltype(nget<M - 1>()(std::move(*this), indices));

    template <class F> // indexing through an array of indices -- a view
    typename std::enable_if<is_numexpr_arg<F>::value &&
                                !is_array_index<F>::value &&
                                !std::is_same<bool, typename F::dtype>::value,
                            numpy_vexpr<numpy_gexpr, F>>::type
    operator[](F const &filter) const
    {
      return {*this, filter};
    }

    template <class F>
    typename std::enable_if<is_numexpr_arg<F>::value &&
                                std::is_same<bool, typename F::dtype>::value,
                            numpy_fexpr<numpy_gexpr, F>>::type
    fast(F const &filter) const;

    template <class F>
    typename std::enable_if<is_numexpr_arg<F>::value &&
                                std::is_same<bool, typename F::dtype>::value,
                            numpy_fexpr<numpy_gexpr, F>>::type
    operator[](F const &filter) const;
    auto operator[](long i) const -> decltype(this->fast(i));
    auto operator[](long i) -> decltype(this->fast(i));

    long flat_size() const;
  };
}

template <class Arg, class... S>
struct returnable<types::numpy_gexpr<Arg, S...>> {
  using type = types::numpy_gexpr<typename returnable<Arg>::type, S...>;
};

template <class T, size_t N, class... S>
struct assignable<types::numpy_gexpr<types::ndarray<T, N> const &, S...>> {
  using type = types::numpy_gexpr<types::ndarray<T, N> const &, S...>;
};

template <class T, size_t N, class... S>
struct assignable<types::numpy_gexpr<types::ndarray<T, N> &, S...>> {
  using type = types::numpy_gexpr<types::ndarray<T, N> &, S...>;
};

template <class Arg, class... S>
struct assignable<types::numpy_gexpr<Arg, S...>> {
  using type = types::numpy_gexpr<typename assignable<Arg>::type, S...>;
};

template <class Arg, class... S>
struct lazy<types::numpy_gexpr<Arg, S...>> {
  using type =
      types::numpy_gexpr<typename lazy<Arg>::type, typename lazy<S>::type...>;
};

template <class Arg, class... S>
struct lazy<types::numpy_gexpr<Arg const &, S...>> {
  using type = types::numpy_gexpr<typename lazy<Arg>::type const &,
                                  typename lazy<S>::type...>;
};
PYTHONIC_NS_END

/* type inference stuff  {*/
#include "pythonic/include/types/combined.hpp"

template <class Arg, class... S>
struct __combined<pythonic::types::numpy_gexpr<Arg, S...>,
                  pythonic::types::numpy_gexpr<Arg, S...>> {
  using type = pythonic::types::numpy_gexpr<Arg, S...>;
};

template <class Arg, class... S, class Argp, class... Sp>
struct __combined<pythonic::types::numpy_gexpr<Arg, S...>,
                  pythonic::types::numpy_gexpr<Argp, Sp...>> {
  using type = pythonic::types::numpy_gexpr<Arg, S...>;
};

template <class Arg, class... S, class O>
struct __combined<pythonic::types::numpy_gexpr<Arg, S...>, O> {
  using type = pythonic::types::numpy_gexpr<Arg, S...>;
};

template <class Arg, class... S, class O>
struct __combined<O, pythonic::types::numpy_gexpr<Arg, S...>> {
  using type = pythonic::types::numpy_gexpr<Arg, S...>;
};

/* combined are sorted such that the assigned type comes first */
template <class Arg, class... S, class T, size_t N>
struct __combined<pythonic::types::numpy_gexpr<Arg, S...>,
                  pythonic::types::ndarray<T, N>> {
  using type = pythonic::types::numpy_gexpr<Arg, S...>;
};

template <class Arg, class... S, class T, size_t N>
struct __combined<pythonic::types::ndarray<T, N>,
                  pythonic::types::numpy_gexpr<Arg, S...>> {
  using type = pythonic::types::ndarray<T, N>;
};

#endif
