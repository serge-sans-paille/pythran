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

    /* specialization of none for integral types we cannot derive from */
    template <class T>
    none<T>::none()
        : data(), is_none(false)
    {
    }

    template <class T>
    none<T>::none(none_type const &)
        : data(), is_none(true)
    {
    }

    template <class T>
    none<T>::none(T const &data)
        : data(data), is_none(false)
    {
    }

    template <class T>
    bool none<T>::operator==(none_type const &) const
    {
      return is_none;
    }

    template <class T>
    bool operator==(T const &t0, none<T> const &t1)
    {
      return not t1.is_none and t1.data == t0;
    }

    template <class T>
    bool operator==(none<T> const &t0, T const &t1)
    {
      return t1 == t0;
    }

    template <class T>
    none<T>::operator T() const
    {
      return data;
    }

    template <class T>
    T &none<T>::operator=(T const &t)
    {
      is_none = false;
      return data = t;
    }

    template <class T>
    intptr_t none<T>::id() const
    {
      return is_none ? NONE_ID : reinterpret_cast<intptr_t>(&data);
    }

    template <class T>
    std::ostream &operator<<(std::ostream &os, none<T> const &v)
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
