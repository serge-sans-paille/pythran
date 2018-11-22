#ifndef PYTHONIC_TYPES_INT_HPP
#define PYTHONIC_TYPES_INT_HPP

#include "pythonic/include/types/int.hpp"
#include "pythonic/types/attr.hpp"

PYTHONIC_NS_BEGIN
namespace __builtin__
{
  template <size_t AttributeID, class T>
  typename std::enable_if<std::is_integral<T>::value, T>::type getattr(T self)
  {
    return AttributeID == pythonic::types::attr::REAL ? self : T(0);
  }
}
PYTHONIC_NS_END

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"
#include "numpy/arrayobject.h"

PYTHONIC_NS_BEGIN

namespace details
{
  constexpr int signed_int_types[] = {0, NPY_INT8, NPY_INT16, 0, NPY_INT32, 0,
                                      0, 0,        NPY_INT64};
  constexpr int unsigned_int_types[] = {
      0, NPY_UINT8, NPY_UINT16, 0, NPY_UINT32, 0, 0, 0, NPY_UINT64};
}

template <class T>
struct c_type_to_numpy_type
    : c_type_to_numpy_type<decltype(std::declval<T>()())> {
};

template <>
struct c_type_to_numpy_type<long double>
    : std::integral_constant<int, NPY_LONGDOUBLE> {
};

template <>
struct c_type_to_numpy_type<double> : std::integral_constant<int, NPY_DOUBLE> {
};

template <>
struct c_type_to_numpy_type<float> : std::integral_constant<int, NPY_FLOAT> {
};

template <>
struct c_type_to_numpy_type<std::complex<float>>
    : std::integral_constant<int, NPY_CFLOAT> {
};

template <>
struct c_type_to_numpy_type<std::complex<double>>
    : std::integral_constant<int, NPY_CDOUBLE> {
};

template <>
struct c_type_to_numpy_type<std::complex<long double>>
    : std::integral_constant<int, NPY_CLONGDOUBLE> {
};

template <>
struct c_type_to_numpy_type<signed long long> {
  static const int value = details::signed_int_types[sizeof(signed long long)];
};

template <>
struct c_type_to_numpy_type<unsigned long long> {
  static const int value =
      details::unsigned_int_types[sizeof(unsigned long long)];
};

template <>
struct c_type_to_numpy_type<signed long> {
  static const int value = details::signed_int_types[sizeof(signed long)];
};

template <>
struct c_type_to_numpy_type<unsigned long> {
  static const int value = details::unsigned_int_types[sizeof(unsigned long)];
};

template <>
struct c_type_to_numpy_type<signed int> {
  static const int value = details::signed_int_types[sizeof(signed int)];
};

template <>
struct c_type_to_numpy_type<unsigned int> {
  static const int value = details::unsigned_int_types[sizeof(unsigned int)];
};

template <>
struct c_type_to_numpy_type<signed short> {
  static const int value = details::signed_int_types[sizeof(signed short)];
};

template <>
struct c_type_to_numpy_type<unsigned short> {
  static const int value = details::unsigned_int_types[sizeof(unsigned short)];
};

template <>
struct c_type_to_numpy_type<signed char> {
  static const int value = details::signed_int_types[sizeof(signed char)];
};

template <>
struct c_type_to_numpy_type<unsigned char> {
  static const int value = details::unsigned_int_types[sizeof(unsigned char)];
};

template <>
struct c_type_to_numpy_type<bool> {
  static const int value = NPY_BOOL;
};

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
    return PyArray_Scalar(                                                     \
        &l, PyArray_DescrFromType(c_type_to_numpy_type<TYPE>::value),          \
        nullptr);                                                              \
  }

PYTHONIC_INT_TO_PYTHON(unsigned char)
PYTHONIC_INT_TO_PYTHON(signed char)
PYTHONIC_INT_TO_PYTHON(unsigned short)
PYTHONIC_INT_TO_PYTHON(signed short)
PYTHONIC_INT_TO_PYTHON(unsigned int)
PYTHONIC_INT_TO_PYTHON(signed int)
PYTHONIC_INT_TO_PYTHON(unsigned long)
PyObject *to_python<signed long>::convert(signed long l)
{
  return PyInt_FromLong(l);
}
PYTHONIC_INT_TO_PYTHON(unsigned long long)
PYTHONIC_INT_TO_PYTHON(signed long long)

#undef PYTHONIC_INT_TO_PYTHON

#define PYTHONIC_INT_FROM_PYTHON(TYPE, NTYPE)                                  \
  bool from_python<TYPE>::is_convertible(PyObject *obj)                        \
  {                                                                            \
    return PyObject_TypeCheck(obj, &Py##NTYPE##ArrType_Type);                  \
  }                                                                            \
  TYPE from_python<TYPE>::convert(PyObject *obj)                               \
  {                                                                            \
    return PyInt_AsLong(obj);                                                  \
  }

PYTHONIC_INT_FROM_PYTHON(unsigned char, UByte)
PYTHONIC_INT_FROM_PYTHON(signed char, Byte)
PYTHONIC_INT_FROM_PYTHON(unsigned short, UShort)
PYTHONIC_INT_FROM_PYTHON(signed short, Short)
PYTHONIC_INT_FROM_PYTHON(unsigned int, UInt)
PYTHONIC_INT_FROM_PYTHON(signed int, Int)
PYTHONIC_INT_FROM_PYTHON(unsigned long, ULong)
bool from_python<signed long>::is_convertible(PyObject *obj)
{
  return PyInt_CheckExact(obj) || PyObject_TypeCheck(obj, &PyLongArrType_Type);
}
signed long from_python<signed long>::convert(PyObject *obj)
{
  return PyLong_AsLong(obj);
}
PYTHONIC_INT_FROM_PYTHON(unsigned long long, ULongLong)
PYTHONIC_INT_FROM_PYTHON(signed long long, LongLong)

#undef PYTHONIC_INT_FROM_PYTHON

PYTHONIC_NS_END
#endif

#endif
