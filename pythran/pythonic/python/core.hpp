#ifndef PYTHONIC_PYTHON_CORE_HPP
#define PYTHONIC_PYTHON_CORE_HPP

#ifdef ENABLE_PYTHON_MODULE

#include "Python.h"
#include <type_traits>
#include <utility>
#include <sstream>

PYTHONIC_NS_BEGIN
template <class T>
struct to_python;

template <class T>
struct from_python;
PYTHONIC_NS_END

template <class T>
auto to_python(T &&value) -> decltype(pythonic::to_python<
    typename std::remove_cv<typename std::remove_reference<T>::type>::type>::
                                          convert(std::forward<T>(value)))
{
  return pythonic::to_python<
      typename std::remove_cv<typename std::remove_reference<T>::type>::type>::
      convert(std::forward<T>(value));
}
template <class T>
T from_python(PyObject *obj)
{
  return pythonic::from_python<T>::convert(obj);
}
template <class T>
bool is_convertible(PyObject *obj)
{
  return pythonic::from_python<T>::is_convertible(obj);
}

PYTHONIC_NS_BEGIN

namespace python
{

#if PY_MAJOR_VERSION >= 3
#ifndef PyString_AS_STRING
#define PyString_AS_STRING (char *) _PyUnicode_COMPACT_DATA
#endif
#endif

  std::nullptr_t raise_invalid_argument(char const name[],
                                        char const alternatives[],
                                        PyObject *args, PyObject *kwargs)
  {
    std::ostringstream oss;
    oss << "Invalid call to pythranized function `" << name << '(';
    for (long n = PyTuple_GET_SIZE(args), i = 0; i < n; ++i) {
      PyObject *repr = PyObject_GetAttrString(
          (PyObject *)Py_TYPE(PyTuple_GET_ITEM(args, i)), "__name__");
      oss << PyString_AS_STRING(repr);
      Py_DECREF(repr);
      if (i != n - 1 || (kwargs && PyDict_Size(kwargs)))
        oss << ", ";
    }

    if (kwargs) {
      PyObject *key, *value;
      Py_ssize_t pos = 0;

      for (int next = PyDict_Next(kwargs, &pos, &key, &value); next;) {
        PyObject *vrepr =
            PyObject_GetAttrString((PyObject *)Py_TYPE(value), "__name__");
        oss << PyString_AS_STRING(key) << '=' << PyString_AS_STRING(vrepr);
        Py_DECREF(vrepr);
        if (next = PyDict_Next(kwargs, &pos, &key, &value))
          oss << ", ";
      }
    }

    oss << ")'\nCandidates are:\n" << alternatives << "\n";

    PyErr_SetString(PyExc_TypeError, oss.str().c_str());
    return nullptr;
  }
}

PYTHONIC_NS_END

#endif

#endif
