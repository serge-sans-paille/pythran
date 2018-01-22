#ifndef PYTHONIC_TYPES_INT_HPP
#define PYTHONIC_TYPES_INT_HPP

#include "pythonic/include/types/int.hpp"

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"

PYTHONIC_NS_BEGIN

#if PY_MAJOR_VERSION >= 3
#ifndef PyInt_FromLong
#define PyInt_FromLong PyLong_FromLong
#endif
#ifndef PyInt_CheckExact
#define PyInt_CheckExact PyLong_CheckExact
#endif
#ifndef PyInt_AsLong
#define PyInt_AsLong PyLong_AsLong
#endif
#endif

#define PYTHONIC_INT_TO_PYTHON(TYPE)                                           \
  PyObject *to_python<TYPE>::convert(TYPE l)                                   \
  {                                                                            \
    return PyInt_FromLong(l);                                                  \
  }

PYTHONIC_INT_TO_PYTHON(unsigned char)
PYTHONIC_INT_TO_PYTHON(signed char)
PYTHONIC_INT_TO_PYTHON(unsigned short)
PYTHONIC_INT_TO_PYTHON(signed short)
PYTHONIC_INT_TO_PYTHON(unsigned int)
PYTHONIC_INT_TO_PYTHON(signed int)
PYTHONIC_INT_TO_PYTHON(unsigned long)
PYTHONIC_INT_TO_PYTHON(signed long)
PYTHONIC_INT_TO_PYTHON(unsigned long long)
PYTHONIC_INT_TO_PYTHON(signed long long)

#undef PYTHONIC_INT_TO_PYTHON

#define PYTHONIC_INT_FROM_PYTHON(TYPE)                                         \
  bool from_python<TYPE>::is_convertible(PyObject *obj)                        \
  {                                                                            \
    return PyInt_CheckExact(obj);                                              \
  }                                                                            \
  TYPE from_python<TYPE>::convert(PyObject *obj)                               \
  {                                                                            \
    return PyInt_AsLong(obj);                                                  \
  }

PYTHONIC_INT_FROM_PYTHON(unsigned char)
PYTHONIC_INT_FROM_PYTHON(signed char)
PYTHONIC_INT_FROM_PYTHON(unsigned short)
PYTHONIC_INT_FROM_PYTHON(signed short)
PYTHONIC_INT_FROM_PYTHON(unsigned int)
PYTHONIC_INT_FROM_PYTHON(signed int)
PYTHONIC_INT_FROM_PYTHON(unsigned long)
PYTHONIC_INT_FROM_PYTHON(signed long)
PYTHONIC_INT_FROM_PYTHON(unsigned long long)
PYTHONIC_INT_FROM_PYTHON(signed long long)

#undef PYTHONIC_INT_FROM_PYTHON
PYTHONIC_NS_END
#endif

#endif
