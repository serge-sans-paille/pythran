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
  bool operator==(std::complex<double> self, long other);
  bool operator==(long self, std::complex<double> other);
  bool operator!=(std::complex<double> self, long other);
  bool operator!=(long self, std::complex<double> other);
}

PYTHONIC_NS_BEGIN
namespace __builtin__
{
  template <size_t AttributeID>
  double getattr(std::complex<double> const &self);
}
PYTHONIC_NS_END

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

#define STD_COMPLEX_IMPLICT_OPERATOR_CAST(op)                                  \
  template <class T, class U>                                                  \
  auto operator op(std::complex<T> const &lhs, std::complex<U> const &rhs)     \
      ->std::complex<typename std::common_type<T, U>::type>                    \
  {                                                                            \
    using ctype = std::complex<typename std::common_type<T, U>::type>;         \
    return ctype{lhs} + ctype{rhs};                                            \
  }

STD_COMPLEX_IMPLICT_OPERATOR_CAST(+)
STD_COMPLEX_IMPLICT_OPERATOR_CAST(-)
STD_COMPLEX_IMPLICT_OPERATOR_CAST(*)
STD_COMPLEX_IMPLICT_OPERATOR_CAST(/ )
STD_COMPLEX_IMPLICT_OPERATOR_CAST(== )
STD_COMPLEX_IMPLICT_OPERATOR_CAST(!= )

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"

PYTHONIC_NS_BEGIN

template <class T>
struct to_python<std::complex<T>> {
  static PyObject *convert(std::complex<T> const &c);
};

template <class T>
struct from_python<std::complex<T>> {
  static bool is_convertible(PyObject *obj);
  static std::complex<T> convert(PyObject *obj);
};
PYTHONIC_NS_END
#endif

#endif
