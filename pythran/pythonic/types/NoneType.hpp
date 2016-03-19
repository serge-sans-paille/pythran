#ifndef PYTHONIC_TYPES_NONE_HPP
#define PYTHONIC_TYPES_NONE_HPP

#include "pythonic/include/types/NoneType.hpp"

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
    none<T, false>::none(none_type const &)
        : T(), is_none(true)
    {
    }

    template <class T>
    template <class... Types>
    none<T, false>::none(Types &&... args)
        : T(std::forward<Types>(args)...), is_none(false)
    {
    }

    template <class T>
    bool none<T, false>::operator==(none_type const &) const
    {
      return is_none;
    }

    template <class T>
    template <class O>
    bool none<T, false>::operator==(O const &t) const
    {
      return not is_none and static_cast<T &>(*this) == t;
    }

    template <class T>
    none<T, false>::operator bool() const
    {
      return not is_none and static_cast<T &>(*this);
    }

    template <class T>
    intptr_t none<T, false>::id() const
    {
      return is_none ? NONE_ID : __builtin__::id(*static_cast<T *>(this));
    }

    /* specialization of none for integral types we cannot derive from */
    template <class T>
    none<T, true>::none()
        : data(), is_none(false)
    {
    }

    template <class T>
    none<T, true>::none(none_type const &)
        : data(), is_none(true)
    {
    }

    template <class T>
    none<T, true>::none(T const &data)
        : data(data), is_none(false)
    {
    }

    template <class T>
    bool none<T, true>::operator==(none_type const &) const
    {
      return is_none;
    }

    template <class T>
    template <class O>
    bool none<T, true>::operator==(O const &t) const
    {
      return not is_none and data == t;
    }

    template <class T>
    none<T, true>::operator bool() const
    {
      return not is_none and data;
    }

    template <class T>
    none<T, true>::operator size_t() const
    {
      return data;
    }

    template <class T>
    none<T, true>::operator long() const
    {
      return data;
    }

    template <class T>
    none<T, true>::operator long long() const
    {
      return data;
    }

    template <class T>
    none<T, true>::operator double() const
    {
      return data;
    }

    template <class T>
    T &none<T, true>::operator=(T const &t)
    {
      is_none = false;
      return data = t;
    }

    template <class T>
    intptr_t none<T, true>::id() const
    {
      return is_none ? NONE_ID : reinterpret_cast<intptr_t>(&data);
    }

    template <class T>
    T operator+(none<T, true> const &t0, T const &t1)
    {
      return t0.data + t1;
    }

    template <class T>
    T operator+(T const &t0, none<T, true> const &t1)
    {
      return t0 + t1.data;
    }

    template <class T>
    none<T, true> operator+(none<T, true> const &t0, none<T, true> const &t1)
    {
      if (t0.is_none and t1.is_none)
        return none_type{};
      else
        return {t0.data + t1.data};
    }

    template <class T>
    bool operator>(none<T, true> const &t0, T const &t1)
    {
      return t0.data > t1;
    }

    template <class T>
    bool operator>(T const &t0, none<T, true> const &t1)
    {
      return t0 > t1.data;
    }

    template <class T>
    none<bool> operator>(none<T, true> const &t0, none<T, true> const &t1)
    {
      if (t0.is_none and t1.is_none)
        return none_type{};
      else
        return {t0.data > t1.data};
    }

    template <class T>
    bool operator>=(none<T, true> const &t0, T const &t1)
    {
      return t0.data >= t1;
    }

    template <class T>
    bool operator>=(T const &t0, none<T, true> const &t1)
    {
      return t0 >= t1.data;
    }

    template <class T>
    none<bool> operator>=(none<T, true> const &t0, none<T, true> const &t1)
    {
      if (t0.is_none and t1.is_none)
        return none_type{};
      else
        return {t0.data >= t1.data};
    }

    template <class T>
    bool operator<(none<T, true> const &t0, T const &t1)
    {
      return t0.data < t1;
    }

    template <class T>
    bool operator<(T const &t0, none<T, true> const &t1)
    {
      return t0 < t1.data;
    }

    template <class T>
    none<bool> operator<(none<T, true> const &t0, none<T, true> const &t1)
    {
      if (t0.is_none and t1.is_none)
        return none_type{};
      else
        return {t0.data < t1.data};
    }

    template <class T>
    bool operator<=(none<T, true> const &t0, T const &t1)
    {
      return t0.data <= t1;
    }

    template <class T>
    bool operator<=(T const &t0, none<T, true> const &t1)
    {
      return t0 <= t1.data;
    }

    template <class T>
    none<bool> operator<=(none<T, true> const &t0, none<T, true> const &t1)
    {
      if (t0.is_none and t1.is_none)
        return none_type{};
      else
        return {t0.data <= t1.data};
    }

    template <class T>
    T operator-(none<T, true> const &t0, T const &t1)
    {
      return t0.data - t1;
    }

    template <class T>
    T operator-(T const &t0, none<T, true> const &t1)
    {
      return t0 - t1.data;
    }

    template <class T>
    none<T, true> operator-(none<T, true> const &t0, none<T, true> const &t1)
    {
      if (t0.is_none and t1.is_none)
        return none_type{};
      else
        return {t0.data - t1.data};
    }

    template <class T>
    T operator*(none<T, true> const &t0, T const &t1)
    {
      return t0.data * t1;
    }

    template <class T>
    T operator*(T const &t0, none<T, true> const &t1)
    {
      return t0 * t1.data;
    }

    template <class T>
    none<T, true> operator*(none<T, true> const &t0, none<T, true> const &t1)
    {
      if (t0.is_none and t1.is_none)
        return none_type{};
      else
        return {t0.data * t1.data};
    }

    template <class T>
    T operator/(none<T, true> const &t0, T const &t1)
    {
      return t0.data / t1;
    }

    template <class T>
    T operator/(T const &t0, none<T, true> const &t1)
    {
      return t0 / t1.data;
    }

    template <class T>
    none<T, true> operator/(none<T, true> const &t0, none<T, true> const &t1)
    {
      if (t0.is_none and t1.is_none)
        return none_type{};
      else
        return {t0.data / t1.data};
    }

    template <class T>
    std::ostream &operator<<(std::ostream &os, none<T, true> const &v)
    {
      if (v.is_none)
        return os << "None";
      else
        return os << v.data;
    }
  }
}

#ifdef ENABLE_PYTHON_MODULE

namespace pythonic
{

  bool from_python<types::none_type>::is_convertible(PyObject *obj)
  {
    return obj == Py_None;
  }

  types::none_type from_python<types::none_type>::convert(PyObject *obj)
  {
    return {};
  }

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
