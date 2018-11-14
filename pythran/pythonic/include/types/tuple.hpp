#ifndef PYTHONIC_INCLUDE_TYPES_TUPLE_HPP
#define PYTHONIC_INCLUDE_TYPES_TUPLE_HPP

#include "pythonic/include/types/assignable.hpp"
#include "pythonic/include/types/traits.hpp"
#include "pythonic/include/types/nditerator.hpp"
#include "pythonic/include/utils/int_.hpp"
#include "pythonic/include/utils/seq.hpp"
#include "pythonic/include/utils/nested_container.hpp"

#include <tuple>
#include <algorithm>

#if !defined(HAVE_SSIZE_T) || !HAVE_SSIZE_T
#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif
#endif

// Equality comparison between pair && tuple
namespace std
{
  template <class F0, class S0, class F1, class S1>
  bool operator==(pair<F0, S0> const &self, tuple<F1, S1> const &other);

  template <class F0, class S0, class F1, class S1>
  bool operator==(pair<const F0, S0> const &self, tuple<F1, S1> const &other);
}

// Tuple concatenation with operator+
template <class... Types0, class... Types1>
std::tuple<Types0..., Types1...> operator+(std::tuple<Types0...> const &t0,
                                           std::tuple<Types1...> const &t1);

template <class... Types0, class... Types1>
std::tuple<Types0..., Types1...> operator+(std::tuple<Types0...> &&t0,
                                           std::tuple<Types1...> const &t1);

template <class... Types0, class... Types1>
std::tuple<Types0..., Types1...> operator+(std::tuple<Types0...> const &t0,
                                           std::tuple<Types1...> &&t1);

template <class... Types0, class... Types1>
std::tuple<Types0..., Types1...> operator+(std::tuple<Types0...> &&t0,
                                           std::tuple<Types1...> &&t1);

PYTHONIC_NS_BEGIN

namespace types
{
  template <class T>
  struct iterator {
    using type = T;
  };

  namespace details
  {
    template <class E, size_t Value>
    void init_shape(array<long, Value> &res, E const &e, utils::int_<1>)
    {
      res[Value - 1] = e.size();
    }
    template <class E, size_t Value, size_t L>
    void init_shape(array<long, Value> &res, E const &e, utils::int_<L>)
    {
      res[Value - L] = e.size();
      init_shape(res, e[0], utils::int_<L - 1>{});
    }
  }

  template <class T>
  class list; // forward declared for array slicing

  template <class T, size_t N>
  struct array;

  template <class T>
  struct is_pod_array {
    static constexpr bool value = false;
  };
  template <class T, size_t N>
  struct is_pod_array<types::array<T, N>> {
    static constexpr bool value = true;
  };

  class str;

  struct slice;
  struct contiguous_slice;

  /* helper to extract the tail of a tuple, && pop the head */
  template <int Offset, class T, size_t... N>
  auto make_tuple_tail(T const &t, utils::index_sequence<N...>)
      -> decltype(std::make_tuple(std::get<Offset + 1 + N>(t)...))
  {
    return std::make_tuple(std::get<Offset + 1 + N>(t)...);
  }

  template <class S, class... Stail>
  std::tuple<Stail...> tuple_tail(std::tuple<S, Stail...> const &t);

  template <class... S>
  struct count_trailing_long : std::integral_constant<size_t, 0> {
  };

  template <class... S>
  struct count_trailing_long<long, S...>
      : std::integral_constant<size_t, 1 + count_trailing_long<S...>::value> {
  };

  template <class S, class... Stail>
  auto tuple_pop(std::tuple<S, Stail...> const &t)
      -> decltype(make_tuple_tail<count_trailing_long<Stail...>::value>(
          t, utils::make_index_sequence<
                 sizeof...(Stail)-count_trailing_long<Stail...>::value>{}))
  {
    return make_tuple_tail<count_trailing_long<Stail...>::value>(
        t, utils::make_index_sequence<sizeof...(
               Stail)-count_trailing_long<Stail...>::value>{});
  }

  template <class A, size_t... I, class... Types>
  std::tuple<Types...> array_to_tuple(A const &a, utils::index_sequence<I...>,
                                      utils::type_sequence<Types...>)
  {
    return std::tuple<Types...>(a[I]...);
  }

  template <class... Tys>
  struct pshape;

  template <class... Tys>
  struct iterator<pshape<Tys...>> {
    using type = array<long, sizeof...(Tys)>;
  };

  template <long N>
  std::integral_constant<long, N> check_type(long value,
                                             std::integral_constant<long, N>)
  {
    assert(N == value && "consistent init");
    return {};
  }
  long check_type(long value, long)
  {
    return value;
  }
  template <long N>
  std::integral_constant<long, N> check_type(std::integral_constant<long, N>,
                                             std::integral_constant<long, N>)
  {
    return {};
  }
  template <long N>
  std::integral_constant<long, N> check_type(std::integral_constant<long, N>,
                                             long v)
  {
    assert(N == v && "consistent init");
    return {};
  }

  template <class T>
  struct is_pshape_element : std::is_integral<T> {
  };
  template <long N>
  struct is_pshape_element<std::integral_constant<long, N>> : std::true_type {
  };

  template <class... Tys>
  struct pshape {
    static_assert(utils::all_of<is_pshape_element<Tys>::value...>::value,
                  "valid pshape");
    struct checked {
    };

    std::tuple<Tys...> values;

    template <class... Args, size_t... Is>
    pshape(std::tuple<Args...> const &v, utils::index_sequence<Is...>)
        : values{check_type(std::get<Is>(v), std::get<Is>(values))...}
    {
    }

    template <class... Args>
    pshape(long arg, Args... args)
        : pshape(std::make_tuple(arg, args...),
                 utils::make_index_sequence<1 + sizeof...(args)>())
    {
    }
    template <class T, T N, class... Args>
    pshape(std::integral_constant<T, N> arg, Args... args)
        : pshape(std::make_tuple(arg, args...),
                 utils::make_index_sequence<1 + sizeof...(args)>())
    {
    }

    template <class S, size_t... Is>
    pshape(S const *buffer, utils::index_sequence<Is...>)
        : values{check_type(buffer[Is], std::get<Is>(values))...}
    {
    }
    template <class S>
    pshape(S const *buffer)
        : pshape(buffer, utils::make_index_sequence<sizeof...(Tys)>())
    {
    }
    template <class... TyOs>
    pshape(pshape<TyOs...> other)
        : pshape(other.values, utils::make_index_sequence<sizeof...(TyOs)>())
    {
      static_assert(sizeof...(TyOs) == sizeof...(Tys), "compatible sizes");
    }

    template <class S>
    pshape(pythonic::types::array<S, sizeof...(Tys)> data)
        : pshape(data.data())
    {
    }

    pshape() = default;
    pshape(pshape const &) = default;
    pshape(pshape &&) = default;
    pshape &operator=(pshape const &) = default;
    pshape &operator=(pshape &&) = default;

    template <size_t... Is>
    types::array<long, sizeof...(Tys)> array(utils::index_sequence<Is...>) const
    {
      return {{get<Is>()...}};
    }

    types::array<long, sizeof...(Tys)> array() const
    {
      return array(utils::make_index_sequence<sizeof...(Tys)>());
    }
    operator types::array<long, sizeof...(Tys)>() const
    {
      return array();
    }

    template <size_t I>
    long get() const
    {
      return std::get<I>(values);
    }
    template <size_t I>
    auto get() -> decltype(std::get<I>(values))
    {
      return std::get<I>(values);
    }
  };

  /* inspired by std::array implementation */
  template <typename T, size_t N>
  struct array {
    using value_type = T;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = value_type *;
    using const_iterator = const value_type *;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // minimal ndarray interface
    using dtype = typename utils::nested_container_value_type<array>::type;
    static const size_t value = utils::nested_container_depth<array>::value;
    static const bool is_vectorizable = true;
    static const bool is_strided = false;

    // flat_size implementation
    template <class E>
    long _flat_size(E const &e, utils::int_<1>) const;
    template <class E, size_t L>
    long _flat_size(E const &e, utils::int_<L>) const;

    long flat_size() const;

    // Support for zero-sized arrays mandatory.
    value_type buffer[N ? N : 1];

    // No explicit construct/copy/destroy for aggregate type.

    void fill(const value_type &__u);

    // Iterators.
    iterator begin() noexcept;
    const_iterator begin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;

    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;

    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    // Capacity.
    constexpr size_type size() const noexcept;
    constexpr size_type max_size() const noexcept;
    constexpr bool empty() const noexcept;

    intptr_t id() const;

    // Element access.
    reference fast(long n);
    constexpr const_reference fast(long n) const noexcept;
#ifdef USE_XSIMD
    using simd_iterator = const_simd_nditerator<array>;
    using simd_iterator_nobroadcast = simd_iterator;
    template <class vectorizer>
    simd_iterator vbegin(vectorizer) const;
    template <class vectorizer>
    simd_iterator vend(vectorizer) const;
#endif

    reference operator[](size_type __n);

    constexpr const_reference operator[](size_type __n) const noexcept;

    reference front();
    const_reference front() const;

    reference back();
    const_reference back() const;

    pointer data() noexcept;
    const_pointer data() const noexcept;

    // operator
    template <size_t M>
    bool operator==(array<T, M> const &other) const;

    template <size_t M>
    bool operator!=(array<T, M> const &other) const;

    template <size_t M>
    bool operator<(array<T, M> const &other) const;

    template <size_t M>
    array<T, N + M> operator+(array<T, M> const &other) const;

    // tuple conversion
    template <class... Types>
    operator std::tuple<Types...>() const;

    template <class Tp>
    operator array<Tp, N>() const;

    auto to_tuple() const
        -> decltype(array_to_tuple(*this, utils::make_index_sequence<N>{},

                                   utils::make_repeated_type<T, N>()));

    numpy_gexpr<array, normalized_slice> operator[](slice const &s) const
    {
      return {*this, s.normalize(size())};
    }
    numpy_gexpr<array, contiguous_normalized_slice>
    operator[](contiguous_slice const &s) const
    {
      return {*this, s.normalize(size())};
    }

    /* array */
    template <class T1, size_t N1>
    friend std::ostream &operator<<(std::ostream &os,
                                    types::array<T1, N1> const &v);

    using shape_t = array<long, value>;
    shape_t shape() const
    {
      array<long, value> res;
      details::init_shape(res, *this, utils::int_<value>{});
      return res;
    }
  };

  // Implementation for detection of "same type".
  // With this information, we know if we must create a real tuple || a
  // static sized array
  namespace details
  {

    template <class... Types>
    struct alike;

    template <>
    struct alike<> {
      static bool const value = false;
      using type = void;
    };

    template <class T>
    struct alike<T> {
      static bool const value = true;
      using type = typename std::remove_cv<
          typename std::remove_reference<T>::type>::type;
    };
    template <class A, class... S>
    struct alike<numpy_gexpr<A, S...>, numpy_gexpr<A const &, S...>> {
      static bool const value = true;
      using type = numpy_gexpr<A, S...>;
    };

    template <class T0, class T1>
    struct alike<T0, T1> {
      static bool const value = std::is_same<T0, T1>::value;
      using type = typename std::conditional<value, T0, void>::type;
    };

    // specialization to make static string alike types::str
    template <size_t N>
    struct alike<char[N], str> {
      static bool const value = true;
      using type = str;
    };

    template <size_t N>
    struct alike<str, char[N]> {
      static bool const value = true;
      using type = str;
    };

    template <size_t N, size_t M>
    struct alike<char[M], char[N]> {
      static bool const value = true;
      using type = str;
    };

    template <class T, size_t N, class... Types>
    struct alike<std::tuple<Types...>, array<T, N>> {
      static bool const value =
          sizeof...(Types) == N &&
          alike<T, typename std::remove_cv<typename std::remove_reference<
                       Types>::type>::type...>::value;
      using type = typename std::conditional<
          value, typename alike<
                     T, typename std::remove_cv<typename std::remove_reference<
                            Types>::type>::type...>::type,
          void>::type;
    };

    template <class T, size_t N, class... Types>
    struct alike<array<T, N>, std::tuple<Types...>>
        : alike<std::tuple<Types...>, array<T, N>> {
    };

    template <class T, class... Types>
    struct alike<T, Types...> {
      static bool const value = alike<Types...>::value &&
                                alike<T, typename alike<Types...>::type>::value;
      using type = typename alike<T, typename alike<Types...>::type>::type;
    };
  }

  template <class... Types>
  struct alike : details::alike<typename std::remove_cv<
                     typename std::remove_reference<Types>::type>::type...> {
  };

  // Pythonic implementation for make_tuple to have the best return type
  // (static array for sames types || real tuple otherwise)
  template <bool Same, class... Types>
  struct _make_tuple {
    auto operator()(Types &&... types)
        -> decltype(std::make_tuple(std::forward<Types>(types)...))
    {
      return std::make_tuple(std::forward<Types>(types)...);
    }
  };

  template <class... Types>
  struct _make_tuple<true, Types...> {
    types::array<typename alike<Types...>::type, sizeof...(Types)>
    operator()(Types &&... types)
    {
      return {{std::forward<Types>(types)...}};
    }
  };

  template <class... Types>
  auto make_tuple(Types &&... types)
#ifndef _MSC_VER
      -> decltype(_make_tuple<alike<Types...>::value, Types...>()(
          std::forward<Types>(types)...))
#endif
  {
    return _make_tuple<alike<Types...>::value, Types...>()(
        std::forward<Types>(types)...);
  }

  template <class T, class Tuple, size_t... S>
  types::array<T, sizeof...(S)> _to_array(Tuple const &t,
                                          utils::index_sequence<S...>)
  {
    return {{T{std::get<S>(t)}...}};
  }

  template <class T, class... Tys>
  types::array<T, sizeof...(Tys)> to_array(std::tuple<Tys...> const &t)
  {
    return _to_array<T>(t, utils::make_index_sequence<sizeof...(Tys)>());
  }

  // Tuple concatenation for array && tuple
  template <class T, size_t N, class... Types>
  auto operator+(std::tuple<Types...> const &t, types::array<T, N> const &lt)
      -> decltype(std::tuple_cat(t, lt.to_tuple()));

  template <class T, size_t N, class... Types>
  auto operator+(types::array<T, N> const &lt, std::tuple<Types...> const &t)
      -> decltype(std::tuple_cat(lt.to_tuple(), t));
}

template <class... Types>
struct assignable<std::tuple<Types...>> {
  using type = std::tuple<typename assignable<Types>::type...>;
};

template <class T, size_t N>
struct assignable<pythonic::types::array<T, N>> {
  using type = pythonic::types::array<typename assignable<T>::type, N>;
};

template <class... Types>
struct returnable<std::tuple<Types...>> {
  using type = std::tuple<typename returnable<Types>::type...>;
};

template <class T, size_t N>
struct returnable<pythonic::types::array<T, N>> {
  using type = pythonic::types::array<typename returnable<T>::type, N>;
};
PYTHONIC_NS_END

/* specialize std::get */
namespace std
{

  template <size_t I, class T, size_t N>
  typename pythonic::types::array<T, N>::reference
  get(pythonic::types::array<T, N> &t);

  template <size_t I, class T, size_t N>
  typename pythonic::types::array<T, N>::const_reference
  get(pythonic::types::array<T, N> const &t);

  template <size_t I, class T, size_t N>
  struct tuple_element<I, pythonic::types::array<T, N>> {
    using type = typename pythonic::types::array<T, N>::value_type;
  };

  template <class T, size_t N>
  struct tuple_size<pythonic::types::array<T, N>> {
    static const size_t value = N;
  };
}

/* hashable tuples, as proposed in
 * http://stackoverflow.com/questions/7110301/generic-hash-for-tuples-in-unordered-map-unordered-set
 */
namespace
{
  inline size_t hash_combiner(size_t left, size_t right); // replacable

  template <size_t index, class... types>
  struct hash_impl {
    size_t operator()(size_t a, const std::tuple<types...> &t) const;
  };

  template <class... types>
  struct hash_impl<0, types...> {
    size_t operator()(size_t a, const std::tuple<types...> &t) const;
  };
}

/* specialize std::hash */
namespace std
{
  template <class... Types>
  struct hash<std::tuple<Types...>> {
    size_t operator()(std::tuple<Types...> const &t) const;
  };

  template <class T, size_t N>
  struct hash<pythonic::types::array<T, N>> {
    size_t operator()(pythonic::types::array<T, N> const &l) const;
  };
}

/* type inference stuff  {*/
#include "pythonic/include/types/combined.hpp"
template <class K, class... Types>
struct __combined<indexable<K>, std::tuple<Types...>> {
  using type = std::tuple<Types...>;
};

template <class K, class... Types>
struct __combined<std::tuple<Types...>, indexable<K>> {
  using type = std::tuple<Types...>;
};

template <class K, class T, size_t N>
struct __combined<indexable<K>, pythonic::types::array<T, N>> {
  using type = pythonic::types::array<T, N>;
};

template <class K, class T, size_t N>
struct __combined<pythonic::types::array<T, N>, indexable<K>> {
  using type = pythonic::types::array<T, N>;
};

template <class K, class T, size_t N>
struct __combined<container<K>, pythonic::types::array<T, N>> {
  using type = pythonic::types::array<typename __combined<T, K>::type, N>;
};

template <class K, class T, size_t N>
struct __combined<pythonic::types::array<T, N>, container<K>> {
  using type = pythonic::types::array<typename __combined<T, K>::type, N>;
};

template <class T, size_t N>
struct __combined<pythonic::types::array<T, N>, pythonic::types::array<T, N>> {
  using type = pythonic::types::array<T, N>;
};

template <class K, class V, class T, size_t N>
struct __combined<indexable_container<K, V>, pythonic::types::array<T, N>> {
  using type = pythonic::types::array<typename __combined<V, T>::type, N>;
};

template <class K, class V, class T, size_t N>
struct __combined<pythonic::types::array<T, N>, indexable_container<K, V>> {
  using type = pythonic::types::array<typename __combined<T, V>::type, N>;
};

template <class... t0, class... t1>
struct __combined<std::tuple<t0...>, std::tuple<t1...>> {
  using type = std::tuple<typename __combined<t0, t1>::type...>; // no further
                                                                 // combination
};
template <class t, class... t0>
struct __combined<std::tuple<t0...>, container<t>> {
  using type = std::tuple<t0...>;
};

template <class t, class... t0>
struct __combined<container<t>, std::tuple<t0...>> {
  using type = std::tuple<t0...>;
};

template <class t, size_t n, class... types>
struct __combined<pythonic::types::array<t, n>, std::tuple<types...>> {
  using type = std::tuple<types...>;
};

template <class t, size_t n, class... types>
struct __combined<std::tuple<types...>, pythonic::types::array<t, n>> {
  using type = std::tuple<types...>;
};
template <class t00, class t01, class t10, class t11>
struct __combined<std::pair<t00, t01>, std::pair<t10, t11>> {
  using type =
      std::pair<typename __combined<t00, t10>::type,
                typename __combined<t01, t11>::type>; // no further combination
};

/* } */

PYTHONIC_NS_BEGIN

namespace types
{

  template <class Tuple, size_t I>
  void print_tuple(std::ostream &os, Tuple const &t, utils::int_<I>);

  template <class Tuple>
  void print_tuple(std::ostream &os, Tuple const &t, utils::int_<0>);

  template <class T, size_t N>
  struct len_of<array<T, N>> {
    static constexpr long value = N;
  };

  template <class... Types>
  struct len_of<std::tuple<Types...>> {
    static constexpr long value = sizeof...(Types);
  };
}
PYTHONIC_NS_END

namespace std
{
  template <class... Args>
  ostream &operator<<(ostream &os, tuple<Args...> const &t);
  template <size_t I, class... Tys>
  long get(pythonic::types::pshape<Tys...> const &s)
  {
    return s.template get<I>();
  }
  template <size_t I, class... Tys>
  auto get(pythonic::types::pshape<Tys...> &s) -> decltype(s.template get<I>())
  {
    return s.template get<I>();
  }
  template <size_t I, class T>
  auto get(T *s) -> decltype(s[I])
  {
    return s[I];
  }
  template <size_t I, class T>
  long get(T const *s)
  {
    return s[I];
  }

  template <class... Tys>
  class tuple_size<pythonic::types::pshape<Tys...>>
      : public std::integral_constant<std::size_t, sizeof...(Tys)>
  {
  };

  template <size_t I, class... Tys>
  struct tuple_element<I, pythonic::types::pshape<Tys...>> {
    using type = typename std::tuple_element < I < sizeof...(Tys) ? I : 0,
          std::tuple<Tys...>> ::type;
  };
}
PYTHONIC_NS_BEGIN
namespace sutils
{

  template <class T>
  struct make_shape {
    using type = T;
  };

  template <class T, size_t N>
  struct make_shape<types::array<T, N>> {
    using type = types::array<long, N>;
  };

  template <class T>
  using shape_t = typename std::enable_if<!std::is_integral<T>::value,
                                          typename make_shape<T>::type>::type;

  template <class Curr, class... Ss>
  struct shape_merger;
  template <class Curr>
  struct shape_merger<Curr> {
    using type = Curr;
  };

  template <class Curr, class... Ss>
  struct shape_merger<Curr, long, Ss...> {
    using type = long;
  };
  template <long N0, long N1, class... Ss>
  struct shape_merger<std::integral_constant<long, N0>,
                      std::integral_constant<long, N1>, Ss...>
      : shape_merger<std::integral_constant<long, (N0 > N1 ? N0 : N1)>, Ss...> {
  };
  template <long N, class... Ss>
  struct shape_merger<long, std::integral_constant<long, N>, Ss...> {
    using type = long;
  };

  template <size_t I, class Ss>
  struct shape_selecter
      : std::conditional<
            (I < std::tuple_size<Ss>::value),
            typename std::tuple_element<
                (I < std::tuple_size<Ss>::value ? I : 0L), Ss>::type,
            std::integral_constant<long, 1>> {
  };

  template <size_t I, class Ss>
  struct merge_shape;
  template <size_t I, class... Ss>
  struct merge_shape<I, std::tuple<Ss...>> {
    using type =
        typename shape_merger<typename shape_selecter<I, Ss>::type...>::type;
  };
  template <class Ss, class T>
  struct merged_shapes;

  template <class Ss, size_t... Is>
  struct merged_shapes<Ss, utils::index_sequence<Is...>> {
    using type = types::pshape<typename merge_shape<Is, Ss>::type...>;
  };

  template <size_t N, class... Ss>
  using merged_shapes_t =
      typename merged_shapes<std::tuple<Ss...>,
                             utils::make_index_sequence<N>>::type;

  template <class T>
  struct transpose;
  template <class T>
  struct transpose<types::array<T, 2>> {
    using type = types::array<T, 2>;
  };

  template <class T0, class T1>
  struct transpose<types::pshape<T0, T1>> {
    using type = types::pshape<T1, T0>;
  };
  template <class T>
  using transpose_t = typename transpose<T>::type;

  template <class T0, class T1>
  void assign(T0 &t0, T1 t1)
  {
    t0 = (T0)t1;
  }
  template <class T0, T0 N, class T1>
  void assign(std::integral_constant<T0, N> &t0, T1 t1)
  {
    assert(t0 == t1 && "consistent");
  }

  template <size_t Start, ssize_t Offset, class T0, class T1, size_t... Is>
  void copy_shape(T0 &shape0, T1 const &shape1, utils::index_sequence<Is...>)
  {
    std::initializer_list<int> _ = {
        (assign(std::get<Start + Is>(shape0),
                std::get<Is + Start + Offset>(shape1)),
         1)...};
  }
  template <class P, class... Tys>
  struct pop_type;

  template <class... Ps, class Ty>
  struct pop_type<types::pshape<Ps...>, Ty> {
    using type = types::pshape<Ps...>;
  };
  template <class... Ps, class Ty, class... Tys>
  struct pop_type<types::pshape<Ps...>, Ty, Tys...>
      : pop_type<types::pshape<Ps..., Ty>, Tys...> {
  };

  template <class T>
  struct pop_tail;

  template <class... Tys>
  struct pop_tail<types::pshape<Tys...>> {
    using type = typename pop_type<types::pshape<>, Tys...>::type;
  };
  template <class T, size_t N>
  struct pop_tail<types::array<T, N>> {
    using type = types::array<T, N - 1>;
  };

  template <class T>
  struct pop_head;

  template <class Ty, class... Tys>
  struct pop_head<types::pshape<Ty, Tys...>> {
    using type = types::pshape<Tys...>;
  };
  template <class T, size_t N>
  struct pop_head<types::array<T, N>> {
    using type = types::array<T, N - 1>;
  };

  template <class T>
  using pop_head_t = typename pop_head<T>::type;

  template <class T>
  using pop_tail_t = typename pop_tail<T>::type;

  template <class... Tys>
  types::array<long, sizeof...(Tys)> array(types::pshape<Tys...> const &pS)
  {
    return pS.array();
  }

  template <class T, size_t N>
  types::array<T, N> array(types::array<T, N> const &pS)
  {
    return pS;
  }

  template <class pS0, class pS1>
  struct concat;

  template <class... Ty0s, class... Ty1s>
  struct concat<types::pshape<Ty0s...>, types::pshape<Ty1s...>> {
    using type = types::pshape<Ty0s..., Ty1s...>;
  };

  template <class... Tys>
  struct concat<types::pshape<Tys...>, types::array<long, 0>> {
    using type = types::pshape<Tys...>;
  };
  template <class... Tys, size_t N>
  struct concat<types::pshape<Tys...>, types::array<long, N>>
      : concat<types::pshape<Tys..., long>, types::array<long, N - 1>> {
  };

  template <class... Ty1s>
  struct concat<types::array<long, 0>, types::pshape<Ty1s...>> {
    using type = types::pshape<Ty1s...>;
  };

  template <size_t N, class... Ty1s>
  struct concat<types::array<long, N>, types::pshape<Ty1s...>>
      : concat<types::array<long, N - 1>, types::pshape<long, Ty1s...>> {
  };

  template <class... Tys>
  using concat_t = typename concat<Tys...>::type;

  template <class P, class T>
  using push_front_t = concat_t<types::pshape<T>, P>;

  template <class S>
  long *find(S &s, long v, std::integral_constant<size_t, 0>)
  {
    return v == std::get<0>(s) ? &std::get<0>(s) : nullptr;
  }
  template <class S, size_t I>
  long *find(S &s, long v, std::integral_constant<size_t, I>)
  {
    return v == std::get<I>(s)
               ? (&std::get<I>(s))
               : find(s, v, std::integral_constant<size_t, I - 1>());
  }

  template <class S>
  long *find(S &s, long v)
  {
    return find(
        s, v, std::integral_constant<size_t, std::tuple_size<S>::value - 1>());
  }

  template <class S, class B>
  bool equals(S const &s, B const &other, std::integral_constant<size_t, 0>)
  {
    return std::get<0>(other) == std::get<0>(s);
  }
  template <class S, class B, size_t I>
  bool equals(S const &s, B const &other, std::integral_constant<size_t, I>)
  {
    return std::get<I>(other) == std::get<I>(s) &&
           equals(s, other, std::integral_constant<size_t, I - 1>());
  }

  template <class S, class B>
  typename std::enable_if<
      std::tuple_size<S>::value == std::tuple_size<B>::value, bool>::type
  equals(S const &s, B const &other)
  {
    return equals(
        s, other,
        std::integral_constant<size_t, std::tuple_size<S>::value - 1>());
  }
  template <class S, class B>
  typename std::enable_if<
      std::tuple_size<S>::value != std::tuple_size<B>::value, bool>::type
  equals(S const &s, B const &other)
  {
    return false;
  }
  template <class S, class B>
  bool equals(S const &s, B *other)
  {
    return equals(
        s, other,
        std::integral_constant<size_t, std::tuple_size<S>::value - 1>());
  }
  template <class S, class B>
  bool requals(S const &s, B const *other, std::integral_constant<size_t, 0>)
  {
    return other[std::tuple_size<S>::value - 1] == std::get<0>(s);
  }
  template <class S, class B, size_t I>
  bool requals(S const &s, B const *other, std::integral_constant<size_t, I>)
  {
    return other[std::tuple_size<S>::value - I - 1] == std::get<I>(s) &&
           requals(s, other, std::integral_constant<size_t, I - 1>());
  }
  template <class S, class B>
  bool requals(S const &s, B const *other)
  {
    return requals(
        s, other,
        std::integral_constant<size_t, std::tuple_size<S>::value - 1>());
  }

  template <class S, class P>
  bool any_of(S const &s, P pred, std::integral_constant<size_t, 0>)
  {
    return pred(std::get<0>(s));
  }
  template <class S, class P, size_t I>
  bool any_of(S const &s, P pred, std::integral_constant<size_t, I>)
  {
    return pred(std::get<I>(s)) ||
           any_of(s, pred, std::integral_constant<size_t, I - 1>());
  }
  template <class S, class Pred>
  bool any_of(S const &s, Pred pred)
  {
    return any_of(
        s, pred,
        std::integral_constant<size_t, std::tuple_size<S>::value - 1>());
  }

  template <class S>
  long min(long curr, S const &s, std::integral_constant<size_t, 0>)
  {
    return std::min(curr, std::get<0>(s));
  }
  template <class S, size_t I>
  long min(long curr, S const &s, std::integral_constant<size_t, I>)
  {
    return min(std::min(curr, std::get<I>(s)), s,
               std::integral_constant<size_t, I - 1>());
  }
  template <class S>
  long min(S const &s)
  {
    return min(std::get<std::tuple_size<S>::value - 1>(s), s,
               std::integral_constant<size_t, std::tuple_size<S>::value - 1>());
  }

  template <class S>
  long prod(S const &s, std::integral_constant<size_t, 0>)
  {
    return std::get<0>(s);
  }
  template <class S, size_t I>
  long prod(S const &s, std::integral_constant<size_t, I>)
  {
    return std::get<I>(s) * prod(s, std::integral_constant<size_t, I - 1>());
  }
  template <class S>
  long prod(S const &s)
  {
    return prod(
        s, std::integral_constant<size_t, std::tuple_size<S>::value - 1>());
  }

  template <class S>
  long prod_tail(S, std::integral_constant<size_t, 0>)
  {
    return 1;
  }
  template <class S, size_t I>
  long prod_tail(S const &s, std::integral_constant<size_t, I>)
  {
    return std::get<I>(s) *
           prod_tail(s, std::integral_constant<size_t, I - 1>());
  }
  template <class S>
  long prod_tail(S const &s)
  {
    return prod_tail(
        s, std::integral_constant<size_t, std::tuple_size<S>::value - 1>());
  }

  template <class S0, class S1, class S2, size_t J>
  typename std::enable_if<(0 < std::tuple_size<S2>::value), void>::type
  copy_new_axis(S0 &s, S1 const &shape, S2 const &new_axis,
                std::integral_constant<size_t, J>,
                std::integral_constant<size_t, 0>)
  {
    if (std::get<0>(new_axis)) {
      std::get<0>(s) = 1;
    } else {
      std::get<0>(s) = std::get<0>(shape);
    }
  }

  template <class S0, class S1, class S2, size_t J>
  typename std::enable_if<(0 >= std::tuple_size<S2>::value), void>::type
  copy_new_axis(S0 &s, S1 const &shape, S2 const &new_axis,
                std::integral_constant<size_t, J>,
                std::integral_constant<size_t, 0>)
  {
    std::get<0>(s) = std::get<J>(shape);
  }

  template <class S0, class S1, class S2, size_t J, size_t I>
  typename std::enable_if<(I < std::tuple_size<S2>::value), void>::type
  copy_new_axis(S0 &s, S1 const &shape, S2 const &new_axis,
                std::integral_constant<size_t, J>,
                std::integral_constant<size_t, I>)
  {
    if (std::get<I>(new_axis)) {
      std::get<I>(s) = 1;
      copy_new_axis(s, shape, new_axis, std::integral_constant<size_t, J>(),
                    std::integral_constant<size_t, I - 1>());
    } else {
      std::get<I>(s) = std::get<J>(shape);
      copy_new_axis(s, shape, new_axis, std::integral_constant < size_t,
                    J == 0 ? J : J - 1 > (),
                    std::integral_constant<size_t, I - 1>());
    }
  }

  template <class S0, class S1, class S2, size_t J, size_t I>
  typename std::enable_if<(I >= std::tuple_size<S2>::value), void>::type
  copy_new_axis(S0 &s, S1 const &shape, S2 const &new_axis,
                std::integral_constant<size_t, J>,
                std::integral_constant<size_t, I>)
  {
    std::get<I>(s) = std::get<J>(shape);
    copy_new_axis(s, shape, new_axis, std::integral_constant<size_t, J - 1>(),
                  std::integral_constant<size_t, I - 1>());
  }

  template <class S0, class S1, class S2>
  S0 copy_new_axis(S0 &s, S1 const &shape, S2 const &new_axis)
  {
    copy_new_axis(
        s, shape, new_axis,
        std::integral_constant<size_t, std::tuple_size<S1>::value - 1>(),
        std::integral_constant<size_t, std::tuple_size<S0>::value - 1>());
    return s;
  }
}

namespace types
{
  template <class T, class... Tys>
  bool operator==(T const &self, pshape<Tys...> const &other)
  {
    return sutils::equals(self, other);
  }
  template <class T, class... Tys>
  bool operator==(pshape<Tys...> const &self, T const &other)
  {
    return sutils::equals(self, other);
  }
  template <class... Ty0s, class... Ty1s>
  bool operator==(pshape<Ty0s...> const &self, pshape<Ty1s...> const &other)
  {
    return sutils::equals(self, other);
  }
  template <class T, class... Tys>
  bool operator!=(T const &self, pshape<Tys...> const &other)
  {
    return !sutils::equals(self, other);
  }
  template <class T, class... Tys>
  bool operator!=(pshape<Tys...> const &self, T const &other)
  {
    return !sutils::equals(self, other);
  }
  template <class... Ty0s, class... Ty1s>
  bool operator!=(pshape<Ty0s...> const &self, pshape<Ty1s...> const &other)
  {
    return !sutils::equals(self, other);
  }
}

PYTHONIC_NS_END

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/include/utils/seq.hpp"
#include "pythonic/include/utils/fwd.hpp"
#include "pythonic/python/core.hpp"

PYTHONIC_NS_BEGIN

template <typename K, typename V>
struct to_python<std::pair<K, V>> {
  static PyObject *convert(std::pair<K, V> const &t);
};

template <typename... Tys>
struct to_python<types::pshape<Tys...>> {
  static PyObject *convert(types::pshape<Tys...> const &t);
};

template <typename... Types>
struct to_python<std::tuple<Types...>> {

  template <size_t... S>
  static PyObject *do_convert(std::tuple<Types...> const &t,
                              utils::index_sequence<S...>);

  static PyObject *convert(std::tuple<Types...> const &t);
};

template <typename T, size_t N>
struct to_python<types::array<T, N>> {
  template <size_t... S>
  static PyObject *do_convert(types::array<T, N> const &t,
                              utils::index_sequence<S...>);

  static PyObject *convert(types::array<T, N> const &t);
};

template <typename... Types>
struct from_python<std::tuple<Types...>> {

  template <size_t... S>
  static bool do_is_convertible(PyObject *obj,
                                typename utils::index_sequence<S...>);

  static bool is_convertible(PyObject *obj);

  template <size_t... S>
  static std::tuple<Types...> do_convert(PyObject *obj,
                                         typename utils::index_sequence<S...>);
  static std::tuple<Types...> convert(PyObject *obj);
};

template <typename T, size_t N>
struct from_python<types::array<T, N>> {

  static bool is_convertible(PyObject *obj);

  template <size_t... S>
  static types::array<T, N> do_convert(PyObject *obj,
                                       typename utils::index_sequence<S...>);
  static types::array<T, N> convert(PyObject *obj);
};
PYTHONIC_NS_END
#endif

#endif
