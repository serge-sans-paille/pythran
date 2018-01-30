#ifndef PYTHONIC_TYPES_TUPLE_HPP
#define PYTHONIC_TYPES_TUPLE_HPP

#include "pythonic/include/types/tuple.hpp"
#include "pythonic/include/types/list.hpp"
#include "pythonic/types/nditerator.hpp"

#include "pythonic/types/assignable.hpp"
#include "pythonic/types/traits.hpp"
#include "pythonic/utils/int_.hpp"
#include "pythonic/utils/seq.hpp"

#include <tuple>
#include <algorithm>

namespace std
{
  template <class F0, class S0, class F1, class S1>
  bool operator==(pair<F0, S0> const &self, tuple<F1, S1> const &other)
  {
    return self.first == get<0>(other) && self.second == get<1>(other);
  }
  template <class F0, class S0, class F1, class S1>
  bool operator==(pair<const F0, S0> const &self, tuple<F1, S1> const &other)
  {
    return self.first == get<0>(other) && self.second == get<1>(other);
  }
}

template <class... Types0, class... Types1>
std::tuple<Types0..., Types1...> operator+(std::tuple<Types0...> const &t0,
                                           std::tuple<Types1...> const &t1)
{
  return std::tuple_cat(t0, t1);
}

template <class... Types0, class... Types1>
std::tuple<Types0..., Types1...> operator+(std::tuple<Types0...> &&t0,
                                           std::tuple<Types1...> const &t1)
{
  return std::tuple_cat(std::forward<Types0...>(t0), t1);
}

template <class... Types0, class... Types1>
std::tuple<Types0..., Types1...> operator+(std::tuple<Types0...> const &t0,
                                           std::tuple<Types1...> &&t1)
{
  return std::tuple_cat(t0, std::forward<Types1...>(t1));
}

template <class... Types0, class... Types1>
std::tuple<Types0..., Types1...> operator+(std::tuple<Types0...> &&t0,
                                           std::tuple<Types1...> &&t1)
{
  return std::tuple_cat(std::forward<Types0...>(t0),
                        std::forward<Types1...>(t1));
}

PYTHONIC_NS_BEGIN

namespace types
{

  /* helper to extract the tail of a tuple, && pop the head
   */
  template <int Offset, class T, size_t... N>
  auto make_tuple_tail(T const &t, utils::index_sequence<N...>)
      -> decltype(std::make_tuple(std::get<Offset + 1 + N>(t)...))
  {
    return std::make_tuple(std::get<Offset + 1 + N>(t)...);
  }

  template <class S, class... Stail>
  std::tuple<Stail...> tuple_tail(std::tuple<S, Stail...> const &t)
  {
    return make_tuple_tail<0>(t,
                              utils::make_index_sequence<sizeof...(Stail)>{});
  }

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

  template <class T, size_t N, class A, size_t... I>
  array<T, N> array_to_array(A const &a, utils::index_sequence<I...>)
  {
    return {a[I]...};
  }

  /* inspired by std::array implementation */
  template <typename T, size_t N>
  template <class E>
  long array<T, N>::_flat_size(E const &e, utils::int_<1>) const
  {
    return N;
  }

  template <typename T, size_t N>
  template <class E, size_t L>
  long array<T, N>::_flat_size(E const &e, utils::int_<L>) const
  {
    return N * _flat_size(e[0], utils::int_<L - 1>{});
  }

  template <typename T, size_t N>
  long array<T, N>::flat_size() const
  {
    return _flat_size(*this, utils::int_<value>{});
  }

  template <typename T, size_t N>
  void array<T, N>::fill(const value_type &__u)
  {
    std::fill_n(begin(), size(), __u);
  }

  // Iterators.
  template <typename T, size_t N>
  typename array<T, N>::iterator array<T, N>::begin() noexcept
  {
    return typename array<T, N>::iterator(data());
  }

  template <typename T, size_t N>
  typename array<T, N>::const_iterator array<T, N>::begin() const noexcept
  {
    return typename array<T, N>::const_iterator(data());
  }

  template <typename T, size_t N>
  typename array<T, N>::iterator array<T, N>::end() noexcept
  {
    return typename array<T, N>::iterator(data() + N);
  }

  template <typename T, size_t N>
  typename array<T, N>::const_iterator array<T, N>::end() const noexcept
  {
    return typename array<T, N>::const_iterator(data() + N);
  }

  template <typename T, size_t N>
  typename array<T, N>::reverse_iterator array<T, N>::rbegin() noexcept
  {
    return typename array<T, N>::reverse_iterator(end());
  }

  template <typename T, size_t N>
  typename array<T, N>::const_reverse_iterator array<T, N>::rbegin() const
      noexcept
  {
    return typename array<T, N>::const_reverse_iterator(end());
  }

  template <typename T, size_t N>
  typename array<T, N>::reverse_iterator array<T, N>::rend() noexcept
  {
    return typename array<T, N>::reverse_iterator(begin());
  }

  template <typename T, size_t N>
  typename array<T, N>::const_reverse_iterator array<T, N>::rend() const
      noexcept
  {
    return typename array<T, N>::const_reverse_iterator(begin());
  }

  template <typename T, size_t N>
  typename array<T, N>::const_iterator array<T, N>::cbegin() const noexcept
  {
    return typename array<T, N>::const_iterator(&(buffer[0]));
  }

  template <typename T, size_t N>
  typename array<T, N>::const_iterator array<T, N>::cend() const noexcept
  {
    return typename array<T, N>::const_iterator(&(buffer[N]));
  }

  template <typename T, size_t N>
  typename array<T, N>::const_reverse_iterator array<T, N>::crbegin() const
      noexcept
  {
    return typename array<T, N>::const_reverse_iterator(end());
  }

  template <typename T, size_t N>
  typename array<T, N>::const_reverse_iterator array<T, N>::crend() const
      noexcept
  {
    return typename array<T, N>::const_reverse_iterator(begin());
  }

  // Capacity.
  template <typename T, size_t N>
  constexpr typename array<T, N>::size_type array<T, N>::size() const noexcept
  {
    return N;
  }

  template <typename T, size_t N>
  constexpr typename array<T, N>::size_type array<T, N>::max_size() const
      noexcept
  {
    return N;
  }

  template <typename T, size_t N>
  constexpr bool array<T, N>::empty() const noexcept
  {
    return size() == 0;
  }

  // Element access.
  template <typename T, size_t N>
  typename array<T, N>::reference array<T, N>::fast(long n)
  {
    return buffer[n];
  }

  template <typename T, size_t N>
  constexpr typename array<T, N>::const_reference
  array<T, N>::fast(long n) const noexcept
  {
    return buffer[n];
  }

#ifdef USE_BOOST_SIMD
  template <class T, size_t N>
  template <class vectorizer>
  typename array<T, N>::simd_iterator array<T, N>::vbegin(vectorizer) const
  {
    return {&buffer[0]};
  }

  template <class T, size_t N>
  template <class vectorizer>
  typename array<T, N>::simd_iterator array<T, N>::vend(vectorizer) const
  {
    using vector_type = typename boost::simd::pack<dtype>;
    static const std::size_t vector_size = vector_type::static_size;
    return {&buffer[long(size() / vector_size * vector_size)]};
  }
#endif

  template <typename T, size_t N>
  typename array<T, N>::reference array<T, N>::
  operator[](typename array<T, N>::size_type __n)
  {
    return buffer[__n];
  }

  template <typename T, size_t N>
  typename array<T, N>::reference
  array<T, N>::fast(typename array<T, N>::size_type __n)
  {
    return buffer[__n];
  }

  template <typename T, size_t N>
  constexpr typename array<T, N>::const_reference array<T, N>::
  operator[](typename array<T, N>::size_type __n) const noexcept
  {
    return buffer[__n];
  }

  template <typename T, size_t N>
  constexpr typename array<T, N>::const_reference
  array<T, N>::fast(typename array<T, N>::size_type __n) const noexcept
  {
    return buffer[__n];
  }

  template <typename T, size_t N>
  typename array<T, N>::reference array<T, N>::front()
  {
    return *begin();
  }

  template <typename T, size_t N>
  typename array<T, N>::const_reference array<T, N>::front() const
  {
    return *begin();
  }

  template <typename T, size_t N>
  typename array<T, N>::reference array<T, N>::back()
  {
    return N ? *(end() - 1) : *end();
  }

  template <typename T, size_t N>
  typename array<T, N>::const_reference array<T, N>::back() const
  {
    return N ? *(end() - 1) : *end();
  }

  template <typename T, size_t N>
  typename array<T, N>::pointer array<T, N>::data() noexcept
  {
    return &(buffer[0]);
  }

  template <typename T, size_t N>
  typename array<T, N>::const_pointer array<T, N>::data() const noexcept
  {
    return &(buffer[0]);
  }

  template <typename T, size_t N>
  template <size_t M>
  bool array<T, N>::operator==(array<T, M> const &other) const
  {
    return N == M && std::equal(begin(), end(), other.begin());
  }

  template <typename T, size_t N>
  template <size_t M>
  bool array<T, N>::operator!=(array<T, M> const &other) const
  {
    return !(*this == other);
  }

  template <typename T, size_t N>
  template <size_t M>
  bool array<T, N>::operator<(array<T, M> const &other) const
  {
    return std::lexicographical_compare(begin(), end(), other.begin(),
                                        other.end());
  }

  template <typename T, size_t N>
  template <size_t M>
  array<T, N + M> array<T, N>::operator+(array<T, M> const &other) const
  {
    array<T, N + M> result;
    auto next = std::copy(begin(), end(), result.begin());
    std::copy(other.begin(), other.end(), next);
    return result;
  }
  template <typename T, size_t N>
  template <class... Types>
  array<T, N>::operator std::tuple<Types...>() const
  {
    return array_to_tuple(*this, utils::make_index_sequence<N>{},
                          typename utils::type_sequence<Types...>{});
  }
  template <typename T, size_t N>
  template <typename Tp>
  array<T, N>::operator array<Tp, N>() const
  {
    return array_to_array<Tp, N>(*this, utils::make_index_sequence<N>{});
  }

  template <typename T, size_t N>
  auto array<T, N>::to_tuple() const
      -> decltype(array_to_tuple(*this, utils::make_index_sequence<N>{},
                                 utils::make_repeated_type<T, N>()))
  {
    return array_to_tuple(*this, utils::make_index_sequence<N>{},
                          utils::make_repeated_type<T, N>());
  }

  /* array */
  template <class T, size_t N>
  std::ostream &operator<<(std::ostream &os, types::array<T, N> const &v)
  {
    os << '(';
    auto iter = v.begin();
    if (iter != v.end()) {
      while (iter + 1 != v.end())
        os << *iter++ << ", ";
      os << *iter;
    }
    return os << ')';
  }

  template <bool Same, class... Types>
  auto _make_tuple<Same, Types...>::operator()(Types &&... types)
      -> decltype(std::make_tuple(std::forward<Types>(types)...))
  {
    return std::make_tuple(std::forward<Types>(types)...);
  }

  template <class... Types>
  types::array<typename alike<Types...>::type, sizeof...(Types)>
      _make_tuple<true, Types...>::operator()(Types &&... types)
  {
    return {{std::forward<Types>(types)...}};
  }

  template <class... Types>
  auto make_tuple(Types &&... types)
      -> decltype(_make_tuple<alike<Types...>::value, Types...>()(
          std::forward<Types>(types)...))
  {
    return _make_tuple<alike<Types...>::value, Types...>()(
        std::forward<Types>(types)...);
  }

  template <class T, size_t N, class... Types>
  auto operator+(std::tuple<Types...> const &t, types::array<T, N> const &lt)
      -> decltype(std::tuple_cat(t, lt.to_tuple()))
  {
    return std::tuple_cat(t, lt.to_tuple());
  }

  template <class T, size_t N, class... Types>
  auto operator+(types::array<T, N> const &lt, std::tuple<Types...> const &t)
      -> decltype(std::tuple_cat(lt.to_tuple(), t))
  {
    return std::tuple_cat(lt.to_tuple(), t);
  }
}
PYTHONIC_NS_END

/* specialize std::get */
namespace std
{
  template <size_t I, class T, size_t N>
  typename pythonic::types::array<T, N>::reference
  get(pythonic::types::array<T, N> &t)
  {
    return t[I];
  }

  template <size_t I, class T, size_t N>
  typename pythonic::types::array<T, N>::const_reference
  get(pythonic::types::array<T, N> const &t)
  {
    return t[I];
  }
}

/* hashable tuples, as proposed in
 * http://stackoverflow.com/questions/7110301/generic-hash-for-tuples-in-unordered-map-unordered-set
 */
namespace
{

  inline size_t hash_combiner(size_t left, size_t right) // replacable
  {
    return left ^ right;
  }

  template <size_t index, class... types>
  size_t hash_impl<index, types...>::
  operator()(size_t a, const std::tuple<types...> &t) const
  {
    using nexttype =
        typename std::tuple_element<index, std::tuple<types...>>::type;
    hash_impl<index - 1, types...> next;
    size_t b = std::hash<nexttype>()(std::get<index>(t));
    return next(hash_combiner(a, b), t);
  }

  template <class... types>
  size_t hash_impl<0, types...>::operator()(size_t a,
                                            const std::tuple<types...> &t) const
  {
    using nexttype = typename std::tuple_element<0, std::tuple<types...>>::type;
    size_t b = std::hash<nexttype>()(std::get<0>(t));
    return hash_combiner(a, b);
  }
}

/* specialize std::hash */
namespace std
{
  template <class... Types>
  size_t hash<std::tuple<Types...>>::
  operator()(std::tuple<Types...> const &t) const
  {
    const size_t begin = std::tuple_size<std::tuple<Types...>>::value - 1;
    return hash_impl<begin, Types...>()(1, t); // 1 should be some largervalue
  }

  template <class T, size_t N>
  size_t hash<pythonic::types::array<T, N>>::
  operator()(pythonic::types::array<T, N> const &l) const
  {
    size_t seed = 0;
    hash<T> h;
    for (auto const &iter : l)
      seed ^= h(iter) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
  }
}

PYTHONIC_NS_BEGIN

namespace types
{
  template <class Tuple, size_t I>
  void print_tuple(std::ostream &os, Tuple const &t, utils::int_<I>)
  {
    print_tuple(os, t, utils::int_<I - 1>());
    os << ", " << std::get<I>(t);
  }

  template <class Tuple>
  void print_tuple(std::ostream &os, Tuple const &t, utils::int_<0>)
  {
    os << std::get<0>(t);
  }
}
PYTHONIC_NS_END

namespace std
{
  template <class... Args>
  ostream &operator<<(ostream &os, tuple<Args...> const &t)
  {
    os << '(';
    pythonic::types::print_tuple(os, t,
                                 pythonic::utils::int_<sizeof...(Args)-1>());
    return os << ')';
  }
}
#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/include/utils/seq.hpp"
#include "pythonic/include/utils/fwd.hpp"
#include "pythonic/python/core.hpp"

PYTHONIC_NS_BEGIN

template <typename K, typename V>
PyObject *to_python<std::pair<K, V>>::convert(std::pair<K, V> const &t)
{
  PyObject *out = PyTuple_New(2);
  PyTuple_SET_ITEM(out, 0, ::to_python(std::get<0>(t)));
  PyTuple_SET_ITEM(out, 1, ::to_python(std::get<1>(t)));
  return out;
}

template <typename... Types>
template <size_t... S>
PyObject *to_python<std::tuple<Types...>>::

    do_convert(std::tuple<Types...> const &t, utils::index_sequence<S...>)
{
  PyObject *out = PyTuple_New(sizeof...(Types));
  std::initializer_list<void *> _ = {
      PyTuple_SET_ITEM(out, S, ::to_python(std::get<S>(t)))...};
  return out;
}

template <typename... Types>
PyObject *
to_python<std::tuple<Types...>>::convert(std::tuple<Types...> const &t)
{
  return do_convert(t, utils::make_index_sequence<sizeof...(Types)>());
}

template <typename T, size_t N>
template <size_t... S>
PyObject *to_python<types::array<T, N>>::do_convert(types::array<T, N> const &t,
                                                    utils::index_sequence<S...>)
{
  PyObject *out = PyTuple_New(N);
  std::initializer_list<void *> _ = {
      PyTuple_SET_ITEM(out, S, ::to_python(std::get<S>(t)))...};
  return out;
}

template <typename T, size_t N>
PyObject *to_python<types::array<T, N>>::convert(types::array<T, N> const &t)
{
  return do_convert(t, utils::make_index_sequence<N>());
}

template <typename... Types>
template <size_t... S>
bool from_python<std::tuple<Types...>>

    ::do_is_convertible(PyObject *obj, typename utils::index_sequence<S...>)
{
  bool checks[] = {::is_convertible<
      typename std::tuple_element<S, std::tuple<Types...>>::type>(
      PyTuple_GET_ITEM(obj, S))...};
  return std::find(std::begin(checks), std::end(checks), false) ==
         std::end(checks);
}

template <typename... Types>
bool from_python<std::tuple<Types...>>::is_convertible(PyObject *obj)
{
  if (PyTuple_Check(obj)) {
    auto n = PyTuple_GET_SIZE(obj);
    if (n == sizeof...(Types)) {
      return do_is_convertible(obj,
                               utils::make_index_sequence<sizeof...(Types)>());
    }
  }
  return false;
}

template <typename... Types>
template <size_t... S>
std::tuple<Types...> from_python<std::tuple<Types...>>::do_convert(
    PyObject *obj, typename utils::index_sequence<S...>)
{
  return std::tuple<Types...>{
      ::from_python<typename std::tuple_element<S, std::tuple<Types...>>::type>(
          PyTuple_GET_ITEM(obj, S))...};
}
template <typename... Types>
std::tuple<Types...> from_python<std::tuple<Types...>>::convert(PyObject *obj)
{
  return do_convert(obj, utils::make_index_sequence<sizeof...(Types)>());
}

template <typename T, size_t N>
bool from_python<types::array<T, N>>::

    is_convertible(PyObject *obj)
{
  if (PyTuple_Check(obj)) {
    auto n = PyTuple_GET_SIZE(obj);
    if (n == N) {
      return ::is_convertible<T>(PyTuple_GET_ITEM(obj, 0));
    }
  }
  return false;
}

template <typename T, size_t N>
template <size_t... S>
types::array<T, N> from_python<types::array<T, N>>::do_convert(
    PyObject *obj, typename utils::index_sequence<S...>)
{
  return {::from_python<T>(PyTuple_GET_ITEM(obj, S))...};
}
template <typename T, size_t N>
types::array<T, N> from_python<types::array<T, N>>::

    convert(PyObject *obj)
{
  return do_convert(obj, utils::make_index_sequence<N>());
}
PYTHONIC_NS_END
#endif

#endif
