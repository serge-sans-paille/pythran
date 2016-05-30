#ifndef PYTHONIC_INCLUDE_TYPES_TUPLE_HPP
#define PYTHONIC_INCLUDE_TYPES_TUPLE_HPP

#include "pythonic/include/types/assignable.hpp"
#include "pythonic/include/types/traits.hpp"
#include "pythonic/include/types/nditerator.hpp"
#include "pythonic/include/utils/int_.hpp"
#include "pythonic/include/utils/seq.hpp"
#include "pythonic/include/utils/nested_container.hpp"

#ifdef USE_BOOST_SIMD
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#endif

#include <tuple>
#include <algorithm>

// Equality comparison between pair and tuple
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

namespace pythonic
{

  namespace types
  {
    template <class T>
    class list; // forward declared for array slicing

    template <class T, size_t N>
    struct array;

    struct str;

    struct slice;

    template <class Arg, class... S>
    struct numpy_gexpr;

    /* helper to extract the tail of a tuple, and pop the head */
    template <int Offset, class T, int... N>
    auto make_tuple_tail(T const &t, utils::seq<N...>)
        -> decltype(std::make_tuple(std::get<Offset + 1 + N>(t)...));

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
            t, typename utils::gens<sizeof...(
                   Stail)-count_trailing_long<Stail...>::value>::type{}));

    template <class A, int... I, class... Types>
    std::tuple<Types...> array_to_tuple(A const &a, utils::seq<I...>,
                                        utils::type_seq<Types...>);

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

      // Element access.
      reference fast(long n);
      constexpr const_reference fast(long n) const noexcept;
#ifdef USE_BOOST_SIMD
      using simd_iterator = const_simd_nditerator<array>;
      simd_iterator vbegin() const;
      simd_iterator vend() const;
      auto load(long i) const -> decltype(boost::simd::load<
          boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>>(&buffer[0], i));

      template <class V>
      void store(V &&v, long i);
#endif

      reference operator[](size_type __n);
      reference fast(size_type __n);

      constexpr const_reference operator[](size_type __n) const noexcept;
      constexpr const_reference fast(size_type __n) const noexcept;

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
      bool operator<(array<T, M> const &other) const;

      template <size_t M>
      array<T, N + M> operator+(array<T, M> const &other) const;

      // tuple conversion
      template <class... Types>
      operator std::tuple<Types...>() const;

      template <class Tp>
      operator array<Tp, N>() const;

      auto to_tuple() const
          -> decltype(array_to_tuple(*this, typename utils::gens<N>::type{},
                                     typename utils::gen_type<N, T>::type{}));

      list<T> operator[](slice const &s); // definition in list.hpp

      /* array */
      template <class T1, size_t N1>
      friend std::ostream &operator<<(std::ostream &os,
                                      types::array<T1, N1> const &v);
      array<long, value> shape() const;
    };

    // Implementation for detection of "same type".
    // With this information, we know if we must create a real tuple or a
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
            sizeof...(Types) == N and
            alike<T, typename std::remove_cv<typename std::remove_reference<
                         Types>::type>::type...>::value;
        using type = typename std::conditional<
            value, typename alike<T, typename std::remove_cv<
                                         typename std::remove_reference<
                                             Types>::type>::type...>::type,
            void>::type;
      };

      template <class T, size_t N, class... Types>
      struct alike<array<T, N>, std::tuple<Types...>>
          : alike<std::tuple<Types...>, array<T, N>> {
      };

      template <class T, class... Types>
      struct alike<T, Types...> {
        static bool const value =
            alike<Types...>::value and
            alike<T, typename alike<Types...>::type>::value;
        using type = typename alike<T, typename alike<Types...>::type>::type;
      };
    }

    template <class... Types>
    struct alike : details::alike<typename std::remove_cv<
                       typename std::remove_reference<Types>::type>::type...> {
    };

    // Pythonic implementation for make_tuple to have the best return type
    // (static array for sames types or real tuple otherwise)
    template <bool Same, class... Types>
    struct _make_tuple {
      auto operator()(Types &&... types)
          -> decltype(std::make_tuple(std::forward<Types>(types)...));
    };

    template <class... Types>
    struct _make_tuple<true, Types...> {
      types::array<typename alike<Types...>::type, sizeof...(Types)>
      operator()(Types &&... types);
    };

    template <class... Types>
    auto make_tuple(Types &&... types)
        -> decltype(_make_tuple<alike<Types...>::value, Types...>()(
            std::forward<Types>(types)...));

    // Tuple concatenation for array and tuple
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
}

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

/* and boost's */
namespace pythonic
{
  namespace types
  {
#ifdef BOOST_NO_CXX11_HDR_TUPLE
    template <class... Types>
    std::size_t hash_value(std::tuple<Types...> const &x);
#endif
    template <class T, size_t N>
    std::size_t hash_value(pythonic::types::array<T, N> const &x);
  }
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

namespace pythonic
{

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
}

namespace std
{
  template <class... Args>
  ostream &operator<<(ostream &os, tuple<Args...> const &t);
}
#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/include/utils/seq.hpp"
#include "pythonic/include/utils/fwd.hpp"
#include "pythonic/python/core.hpp"

namespace pythonic
{

  template <typename K, typename V>
  struct to_python<std::pair<K, V>> {
    static PyObject *convert(std::pair<K, V> const &t);
  };

  template <typename... Types>
  struct to_python<std::tuple<Types...>> {

    template <int... S>
    static PyObject *do_convert(std::tuple<Types...> const &t,
                                utils::seq<S...>);

    static PyObject *convert(std::tuple<Types...> const &t);
  };

  template <typename T, size_t N>
  struct to_python<types::array<T, N>> {
    template <int... S>
    static PyObject *do_convert(types::array<T, N> const &t, utils::seq<S...>);

    static PyObject *convert(types::array<T, N> const &t);
  };

  template <typename... Types>
  struct from_python<std::tuple<Types...>> {

    template <int... S>
    static bool do_is_convertible(PyObject *obj, typename utils::seq<S...>);

    static bool is_convertible(PyObject *obj);

    template <int... S>
    static std::tuple<Types...> do_convert(PyObject *obj,
                                           typename utils::seq<S...>);
    static std::tuple<Types...> convert(PyObject *obj);
  };

  template <typename T, size_t N>
  struct from_python<types::array<T, N>> {

    static bool is_convertible(PyObject *obj);

    template <int... S>
    static types::array<T, N> do_convert(PyObject *obj,
                                         typename utils::seq<S...>);
    static types::array<T, N> convert(PyObject *obj);
  };
}
#endif

#endif
