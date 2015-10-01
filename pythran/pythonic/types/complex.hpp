#ifndef PYTHONIC_TYPES_COMPLEX_HPP
#define PYTHONIC_TYPES_COMPLEX_HPP

#include "pythonic/include/types/complex.hpp"

#include "pythonic/types/attr.hpp"

namespace std
{
  std::complex<double> operator+(std::complex<double> self, long other)
  {
    return self + double(other);
  }

  std::complex<double> operator+(long self, std::complex<double> other)
  {
    return double(self) + other;
  }

  std::complex<double> operator-(std::complex<double> self, long other)
  {
    return self - double(other);
  }

  std::complex<double> operator-(long self, std::complex<double> other)
  {
    return double(self) - other;
  }

  std::complex<double> operator*(std::complex<double> self, long other)
  {
    return self * double(other);
  }

  std::complex<double> operator*(long self, std::complex<double> other)
  {
    return double(self) * other;
  }

  std::complex<double> operator/(std::complex<double> self, long other)
  {
    return self / double(other);
  }

  std::complex<double> operator/(long self, std::complex<double> other)
  {
    return double(self) / other;
  }
}

namespace pythonic
{

  namespace __builtin__
  {

    template <size_t AttributeID>
    double getattr(std::complex<double> const &self)
    {
      return AttributeID == pythonic::types::attr::REAL ? std::real(self)
                                                        : std::imag(self);
    }
  }
}

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"

namespace pythonic
{

  template <class T>
  PyObject *to_python<std::complex<T>>::convert(std::complex<T> const &c)
  {
    return PyComplex_FromDoubles(c.real(), c.imag());
  }

  template <class T>
  bool from_python<std::complex<T>>::is_convertible(PyObject *obj)
  {
    return PyComplex_Check(obj) or PyFloat_Check(obj) or PyInt_Check(obj);
  }
  template <class T>
  std::complex<T> from_python<std::complex<T>>::convert(PyObject *obj)
  {
    if (PyComplex_Check(obj))
      return {PyComplex_RealAsDouble(obj), PyComplex_ImagAsDouble(obj)};
    else if (PyFloat_Check(obj))
      return {PyFloat_AsDouble(obj), 0.};
    else
      return {(double)PyInt_AsLong(obj), 0.};
  }
}
#endif

#endif
