#ifndef PYTHONIC_TYPES_NONE_HPP
#define PYTHONIC_TYPES_NONE_HPP

#include "pythonic/include/types/none.hpp"

#include "pythonic/types/assignable.hpp"
#include "pythonic/__builtin__/id.hpp"

namespace pythonic
{

  namespace types
  {

    /// none_type implementation
    none_type::none_type()
    {
    }

    intptr_t none_type::id() const
    {
      return NONE_ID;
    }

    /// none implementation
    /* Type adapator to simulate an option type
     *
     * see http://en.wikipedia.org/wiki/Option_type
     */
    template <class T>
    none<T>::none(none_type const &)
        : T(), is_none(true)
    {
    }

    template <class T>
    template <class... Types>
    none<T>::none(Types &&... args)
        : T(std::forward<Types>(args)...), is_none(false)
    {
    }

    template <class T>
    bool none<T>::operator==(none_type const &) const
    {
      return is_none;
    }

    template <class T>
    template <class O>
    bool none<T>::operator==(O const &t) const
    {
      return not is_none and static_cast<T &>(*this) == t;
    }

    template <class T>
    none<T>::operator bool() const
    {
      return not is_none and static_cast<T &>(*this);
    }

    template <class T>
    intptr_t none<T>::id() const
    {
      return is_none ? NONE_ID : __builtin__::id(*static_cast<T *>(this));
    }

/* specialization of none for integral types we cannot derive from */
#define SPECIALIZE_NONE_IMPL(T)                                                \
  none<T>::none() : data(), is_none(false)                                     \
  {                                                                            \
  }                                                                            \
                                                                               \
  none<T>::none(none_type const &) : data(), is_none(true)                     \
  {                                                                            \
  }                                                                            \
                                                                               \
  none<T>::none(T const &data) : data(data), is_none(false)                    \
  {                                                                            \
  }                                                                            \
                                                                               \
  bool none<T>::operator==(none_type const &) const                            \
  {                                                                            \
    return is_none;                                                            \
  }                                                                            \
                                                                               \
  template <class O>                                                           \
  bool none<T>::operator==(O const &t) const                                   \
  {                                                                            \
    return not is_none and data == t;                                          \
  }                                                                            \
                                                                               \
  none<T>::operator bool() const                                               \
  {                                                                            \
    return not is_none and data;                                               \
  }                                                                            \
                                                                               \
  none<T>::operator size_t() const                                             \
  {                                                                            \
    return data;                                                               \
  }                                                                            \
                                                                               \
  none<T>::operator long() const                                               \
  {                                                                            \
    return data;                                                               \
  }                                                                            \
                                                                               \
  none<T>::operator long long() const                                          \
  {                                                                            \
    return data;                                                               \
  }                                                                            \
                                                                               \
  none<T>::operator double() const                                             \
  {                                                                            \
    return data;                                                               \
  }                                                                            \
                                                                               \
  T &none<T>::operator=(T const &t)                                            \
  {                                                                            \
    is_none = false;                                                           \
    return data = t;                                                           \
  }                                                                            \
                                                                               \
  intptr_t none<T>::id() const                                                 \
  {                                                                            \
    return is_none ? NONE_ID : reinterpret_cast<intptr_t>(&data);              \
  }                                                                            \
                                                                               \
  T operator+(none<T> const &t0, T const &t1)                                  \
  {                                                                            \
    return t0.data + t1;                                                       \
  }                                                                            \
                                                                               \
  T operator+(T const &t0, none<T> const &t1)                                  \
  {                                                                            \
    return t0 + t1.data;                                                       \
  }                                                                            \
                                                                               \
  none<T> operator+(none<T> const &t0, none<T> const &t1)                      \
  {                                                                            \
    if (t0.is_none and t1.is_none)                                             \
      return none_type{};                                                      \
    else                                                                       \
      return {t0.data + t1.data};                                              \
  }                                                                            \
                                                                               \
  bool operator>(none<T> const &t0, T const &t1)                               \
  {                                                                            \
    return t0.data > t1;                                                       \
  }                                                                            \
                                                                               \
  bool operator>(T const &t0, none<T> const &t1)                               \
  {                                                                            \
    return t0 > t1.data;                                                       \
  }                                                                            \
                                                                               \
  none<bool> operator>(none<T> const &t0, none<T> const &t1)                   \
  {                                                                            \
    if (t0.is_none and t1.is_none)                                             \
      return none_type{};                                                      \
    else                                                                       \
      return {t0.data > t1.data};                                              \
  }                                                                            \
                                                                               \
  bool operator>=(none<T> const &t0, T const &t1)                              \
  {                                                                            \
    return t0.data >= t1;                                                      \
  }                                                                            \
                                                                               \
  bool operator>=(T const &t0, none<T> const &t1)                              \
  {                                                                            \
    return t0 >= t1.data;                                                      \
  }                                                                            \
                                                                               \
  none<bool> operator>=(none<T> const &t0, none<T> const &t1)                  \
  {                                                                            \
    if (t0.is_none and t1.is_none)                                             \
      return none_type{};                                                      \
    else                                                                       \
      return {t0.data >= t1.data};                                             \
  }                                                                            \
                                                                               \
  bool operator<(none<T> const &t0, T const &t1)                               \
  {                                                                            \
    return t0.data < t1;                                                       \
  }                                                                            \
                                                                               \
  bool operator<(T const &t0, none<T> const &t1)                               \
  {                                                                            \
    return t0 < t1.data;                                                       \
  }                                                                            \
                                                                               \
  none<bool> operator<(none<T> const &t0, none<T> const &t1)                   \
  {                                                                            \
    if (t0.is_none and t1.is_none)                                             \
      return none_type{};                                                      \
    else                                                                       \
      return {t0.data < t1.data};                                              \
  }                                                                            \
                                                                               \
  bool operator<=(none<T> const &t0, T const &t1)                              \
  {                                                                            \
    return t0.data <= t1;                                                      \
  }                                                                            \
                                                                               \
  bool operator<=(T const &t0, none<T> const &t1)                              \
  {                                                                            \
    return t0 <= t1.data;                                                      \
  }                                                                            \
                                                                               \
  none<bool> operator<=(none<T> const &t0, none<T> const &t1)                  \
  {                                                                            \
    if (t0.is_none and t1.is_none)                                             \
      return none_type{};                                                      \
    else                                                                       \
      return {t0.data <= t1.data};                                             \
  }                                                                            \
                                                                               \
  T operator-(none<T> const &t0, T const &t1)                                  \
  {                                                                            \
    return t0.data - t1;                                                       \
  }                                                                            \
                                                                               \
  T operator-(T const &t0, none<T> const &t1)                                  \
  {                                                                            \
    return t0 - t1.data;                                                       \
  }                                                                            \
                                                                               \
  none<T> operator-(none<T> const &t0, none<T> const &t1)                      \
  {                                                                            \
    if (t0.is_none and t1.is_none)                                             \
      return none_type{};                                                      \
    else                                                                       \
      return {t0.data - t1.data};                                              \
  }                                                                            \
                                                                               \
  T operator*(none<T> const &t0, T const &t1)                                  \
  {                                                                            \
    return t0.data * t1;                                                       \
  }                                                                            \
                                                                               \
  T operator*(T const &t0, none<T> const &t1)                                  \
  {                                                                            \
    return t0 * t1.data;                                                       \
  }                                                                            \
                                                                               \
  none<T> operator*(none<T> const &t0, none<T> const &t1)                      \
  {                                                                            \
    if (t0.is_none and t1.is_none)                                             \
      return none_type{};                                                      \
    else                                                                       \
      return {t0.data * t1.data};                                              \
  }                                                                            \
                                                                               \
  T operator/(none<T> const &t0, T const &t1)                                  \
  {                                                                            \
    return t0.data / t1;                                                       \
  }                                                                            \
                                                                               \
  T operator/(T const &t0, none<T> const &t1)                                  \
  {                                                                            \
    return t0 / t1.data;                                                       \
  }                                                                            \
                                                                               \
  none<T> operator/(none<T> const &t0, none<T> const &t1)                      \
  {                                                                            \
    if (t0.is_none and t1.is_none)                                             \
      return none_type{};                                                      \
    else                                                                       \
      return {t0.data / t1.data};                                              \
  }                                                                            \
                                                                               \
  std::ostream &operator<<(std::ostream &os, none<T> const &v)                 \
  {                                                                            \
    if (v.is_none)                                                             \
      return os << "None";                                                     \
    else                                                                       \
      return os << v.data;                                                     \
  }

    SPECIALIZE_NONE_IMPL(bool);
    SPECIALIZE_NONE_IMPL(size_t);
    SPECIALIZE_NONE_IMPL(long);
    SPECIALIZE_NONE_IMPL(int);
    SPECIALIZE_NONE_IMPL(long long);
    SPECIALIZE_NONE_IMPL(double);
  }
}

#ifdef ENABLE_PYTHON_MODULE

namespace pythonic
{
  PyObject *to_python<types::none_type>::convert(types::none_type)
  {
    Py_RETURN_NONE;
  }

  template <class T>
  PyObject *to_python<types::none<T>>::convert(types::none<T> const &n)
  {
    if (n.is_none) {
      Py_RETURN_NONE;
    } else {
      return ::to_python(static_cast<T const &>(n));
    }
  }
}

#endif

#endif
