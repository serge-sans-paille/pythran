#ifndef PYTHONIC_TYPES_COMPLEX_HPP
#define PYTHONIC_TYPES_COMPLEX_HPP

#include "pythonic/include/types/complex.hpp"
#include "pythonic/numpy/complex64.hpp"
#include "pythonic/numpy/complex128.hpp"
#include "pythonic/numpy/complex256.hpp"

#include "pythonic/types/attr.hpp"

namespace std
{
  template <class T, class S>
  complex_broadcast_t<T, S> operator+(std::complex<T> self, S other)
  {
    return (complex_broadcast_t<T, S>)self +
           (typename std::common_type<T, S>::type)(other);
  }

  template <class T, class S>
  complex_broadcast_t<T, S> operator+(S self, std::complex<T> other)
  {
    return (typename std::common_type<T, S>::type)(self) +
           (complex_broadcast_t<T, S>)other;
  }

  template <class T, class S>
  complex_broadcast_t<T, S> operator-(std::complex<T> self, S other)
  {
    return (complex_broadcast_t<T, S>)self -
           (typename std::common_type<T, S>::type)(other);
  }

  template <class T, class S>
  complex_broadcast_t<T, S> operator-(S self, std::complex<T> other)
  {
    return (typename std::common_type<T, S>::type)(self) -
           (complex_broadcast_t<T, S>)other;
  }

  template <class T, class S>
  complex_broadcast_t<T, S> operator*(std::complex<T> self, S other)
  {
    return (complex_broadcast_t<T, S>)self *
           (typename std::common_type<T, S>::type)(other);
  }

  template <class T, class S>
  complex_broadcast_t<T, S> operator*(S self, std::complex<T> other)
  {
    return (typename std::common_type<T, S>::type)(self) *
           (complex_broadcast_t<T, S>)other;
  }

  template <class T, class S>
  complex_broadcast_t<T, S> operator/(std::complex<T> self, S other)
  {
    return (complex_broadcast_t<T, S>)self /
           (typename std::common_type<T, S>::type)(other);
  }

  template <class T, class S>
  complex_broadcast_t<T, S> operator/(S self, std::complex<T> other)
  {
    return (typename std::common_type<T, S>::type)(self) /
           (complex_broadcast_t<T, S>)other;
  }

  template <class T, class S>
  complex_bool_t<T, S> operator==(std::complex<T> self, S other)
  {
    return self == T(other);
  }

  template <class T, class S>
  complex_bool_t<T, S> operator==(S self, std::complex<T> other)
  {
    return T(self) == other;
  }

  template <class T, class S>
  complex_bool_t<T, S> operator!=(std::complex<T> self, S other)
  {
    return self != T(other);
  }

  template <class T, class S>
  complex_bool_t<T, S> operator!=(S self, std::complex<T> other)
  {
    return T(self) != other;
  }

  template <class T, class S>
  bool operator<(std::complex<T> self, std::complex<S> other)
  {
    return self.real() == other.real() ? self.imag() < other.imag()
                                       : self.real() < other.real();
  }

  template <class T, class S>
  bool operator<=(std::complex<T> self, std::complex<S> other)
  {
    return self.real() == other.real() ? self.imag() <= other.imag()
                                       : self.real() <= other.real();
  }

  template <class T, class S>
  bool operator>(std::complex<T> self, std::complex<S> other)
  {
    return self.real() == other.real() ? self.imag() > other.imag()
                                       : self.real() > other.real();
  }

  template <class T, class S>
  bool operator>=(std::complex<T> self, std::complex<S> other)
  {
    return self.real() == other.real() ? self.imag() >= other.imag()
                                       : self.real() >= other.real();
  }

  template <class T, class S>
  bool operator&&(std::complex<T> self, std::complex<S> other)
  {
    return (self.real() || self.imag()) && (other.real() || other.imag());
  }

  template <class T, class S>
  bool operator||(std::complex<T> self, std::complex<S> other)
  {
    return (self.real() || self.imag()) || (other.real() || other.imag());
  }
  template <class T>
  bool operator!(std::complex<T> self)
  {
    return !self.real() && !self.imag();
  }
  template <class T>
  size_t hash<std::complex<T>>::operator()(std::complex<T> const &x) const
  {
    return std::hash<T>{}(x.real()) ^ std::hash<T>{}(x.imag());
  };
}

PYTHONIC_NS_BEGIN

namespace builtins
{

  template <class T>
  T getattr(types::attr::REAL, std::complex<T> const &self)
  {
    return std::real(self);
  }
  template <class T>
  T getattr(types::attr::IMAG, std::complex<T> const &self)
  {
    return std::imag(self);
  }
  numpy::functor::complex64 getattr(types::attr::DTYPE,
                                    std::complex<float> const &self)
  {
    return {};
  }
  numpy::functor::complex128 getattr(types::attr::DTYPE,
                                     std::complex<double> const &self)
  {
    return {};
  }
  numpy::functor::complex256 getattr(types::attr::DTYPE,
                                     std::complex<long double> const &self)
  {
    return {};
  }
}
PYTHONIC_NS_END

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"
#include "numpy/arrayscalars.h"

PYTHONIC_NS_BEGIN

template <>
PyObject *to_python<std::complex<long double>>::convert(
    std::complex<long double> const &c)
{
  return PyArray_Scalar(const_cast<std::complex<long double> *>(&c),
                        PyArray_DescrFromType(NPY_CLONGDOUBLE), nullptr);
}

template <>
PyObject *
to_python<std::complex<double>>::convert(std::complex<double> const &c)
{
  return PyComplex_FromDoubles(c.real(), c.imag());
}

template <>
PyObject *to_python<std::complex<float>>::convert(std::complex<float> const &c)
{
  return PyArray_Scalar(const_cast<std::complex<float> *>(&c),
                        PyArray_DescrFromType(NPY_CFLOAT), nullptr);
}

template <>
bool from_python<std::complex<long double>>::is_convertible(PyObject *obj)
{
  return PyArray_IsScalar(obj, CLongDouble);
}

template <>
bool from_python<std::complex<double>>::is_convertible(PyObject *obj)
{
  return PyComplex_Check(obj);
}

template <>
bool from_python<std::complex<float>>::is_convertible(PyObject *obj)
{
  return PyArray_IsScalar(obj, CFloat);
}

template <>
std::complex<long double>
from_python<std::complex<long double>>::convert(PyObject *obj)
{
  auto val = PyArrayScalar_VAL(obj, CLongDouble);
  return {val.real, val.imag};
}

template <>
std::complex<double> from_python<std::complex<double>>::convert(PyObject *obj)
{
  return {PyComplex_RealAsDouble(obj), PyComplex_ImagAsDouble(obj)};
}

template <>
std::complex<float> from_python<std::complex<float>>::convert(PyObject *obj)
{
  auto val = PyArrayScalar_VAL(obj, CFloat);
  return {val.real, val.imag};
}
PYTHONIC_NS_END
#endif

#endif
