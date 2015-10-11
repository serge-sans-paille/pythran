#ifndef PYTHONIC_TYPES_FLOAT_HPP
#define PYTHONIC_TYPES_FLOAT_HPP

#include "pythonic/include/types/float.hpp"

#include "pythonic/types/attr.hpp"
#include <cstddef>

namespace pythonic
{
  namespace __builtin__
  {
    template <size_t AttributeID>
    double getattr(double self)
    {
      return AttributeID == pythonic::types::attr::REAL ? self : 0.;
    }
  }
}

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"

namespace pythonic
{

  PyObject *to_python<double>::convert(double d)
  {
    return PyFloat_FromDouble(d);
  }
  PyObject *to_python<float>::convert(float d)
  {
    return PyFloat_FromDouble(d);
  }

  bool from_python<double>::is_convertible(PyObject *obj)
  {
    return PyFloat_Check(obj) or PyInt_Check(obj);
  }
  double from_python<double>::convert(PyObject *obj)
  {
    if (PyFloat_Check(obj))
      return PyFloat_AsDouble(obj);
    else
      return PyInt_AsLong(obj);
  }

  bool from_python<float>::is_convertible(PyObject *obj)
  {
    return PyFloat_Check(obj) or PyInt_Check(obj);
  }
  float from_python<float>::convert(PyObject *obj)
  {
    if (PyFloat_Check(obj))
      return PyFloat_AsDouble(obj);
    else
      return PyInt_AsLong(obj);
  }
}

#endif

#endif
