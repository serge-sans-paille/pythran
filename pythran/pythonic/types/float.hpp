#ifndef PYTHONIC_TYPES_FLOAT_HPP
#define PYTHONIC_TYPES_FLOAT_HPP

#include "pythonic/include/types/float.hpp"

#include "pythonic/types/attr.hpp"
#include <cstddef>

PYTHONIC_NS_BEGIN
namespace __builtin__
{
  template <size_t AttributeID>
  double getattr(double self)
  {
    return AttributeID == pythonic::types::attr::REAL ? self : 0.;
  }
}
PYTHONIC_NS_END

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"
#include "numpy/arrayscalars.h"
#include <iostream>

PYTHONIC_NS_BEGIN

PyObject *to_python<long double>::convert(long double d)
{
  return PyArray_Scalar(&d, PyArray_DescrFromType(NPY_LONGDOUBLE), nullptr);
}

PyObject *to_python<double>::convert(double d)
{
  return PyFloat_FromDouble(d);
}
PyObject *to_python<float>::convert(float d)
{
  return PyFloat_FromDouble(d);
}

bool from_python<long double>::is_convertible(PyObject *obj)
{
  return PyFloat_Check(obj) || PyArray_IsScalar(obj, LongDouble);
}

long double from_python<long double>::convert(PyObject *obj)
{
  if (PyArray_IsScalar(obj, LongDouble))
    return PyArrayScalar_VAL(obj, LongDouble);
  else if (PyFloat_Check(obj))
    return PyFloat_AsDouble(obj);
  else
    return PyInt_AsLong(obj);
}

bool from_python<double>::is_convertible(PyObject *obj)
{
  return PyFloat_Check(obj);
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
  return PyFloat_Check(obj);
}
float from_python<float>::convert(PyObject *obj)
{
  return PyFloat_AsDouble(obj);
}
PYTHONIC_NS_END

#endif

#endif
