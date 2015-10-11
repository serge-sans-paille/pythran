#ifndef PYTHONIC_PYTHON_CORE_HPP
#define PYTHONIC_PYTHON_CORE_HPP

#ifdef ENABLE_PYTHON_MODULE

#include "Python.h"

namespace pythonic
{
  template <class T>
  struct to_python;

  template <class T>
  struct from_python;
}

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

#endif

#endif
