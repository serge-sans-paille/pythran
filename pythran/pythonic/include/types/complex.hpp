#ifndef PYTHONIC_INCLUDE_TYPES_COMPLEX_HPP
#define PYTHONIC_INCLUDE_TYPES_COMPLEX_HPP

#include <complex>

namespace std
{
  std::complex<double> operator+(std::complex<double> self, long other);
  std::complex<double> operator+(long self, std::complex<double> other);
  std::complex<double> operator-(std::complex<double> self, long other);
  std::complex<double> operator-(long self, std::complex<double> other);
  std::complex<double> operator*(std::complex<double> self, long other);
  std::complex<double> operator*(long self, std::complex<double> other);
  std::complex<double> operator/(std::complex<double> self, long other);
  std::complex<double> operator/(long self, std::complex<double> other);
}

namespace pythonic
{
  namespace __builtin__
  {
    template <size_t AttributeID>
    double getattr(std::complex<double> const &self);
  }
}

/* for type inference { */

#include "pythonic/include/types/combined.hpp"
template <class K>
struct __combined<indexable<K>, std::complex<double>> {
  using type = std::complex<double>;
};

template <class K>
struct __combined<std::complex<double>, indexable<K>> {
  using type = std::complex<double>;
};

/* } */

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"

namespace pythonic
{

  template <class T>
  struct to_python<std::complex<T>> {
    static PyObject *convert(std::complex<T> const &c);
  };

  template <class T>
  struct from_python<std::complex<T>> {
    static bool is_convertible(PyObject *obj);
    static std::complex<T> convert(PyObject *obj);
  };
}
#endif

#endif
