#ifndef PYTHONIC_TYPES_BOOL_HPP
#define PYTHONIC_TYPES_BOOL_HPP

#include "pythonic/include/types/bool.hpp"

#ifdef ENABLE_PYTHON_MODULE

namespace pythonic
{
  PyObject *to_python<bool>::convert(bool b)
  {
    if (b)
      Py_RETURN_TRUE;
    else
      Py_RETURN_FALSE;
  }

  bool from_python<bool>::is_convertible(PyObject *obj)
  {
    return PyBool_Check(obj);
  }
  bool from_python<bool>::convert(PyObject *obj)
  {
    return PyInt_AsLong(obj);
  }
}

#endif

#endif
