#ifndef PYTHONIC_INCLUDE_TYPES_COMPLEX_HPP
#define PYTHONIC_INCLUDE_TYPES_COMPLEX_HPP

#include <complex>

namespace std
{

  template <class T, class S>
  using complex_broadcast_t = typename std::enable_if<
      std::is_scalar<S>::value && !std::is_same<T, S>::value,
      std::complex<typename std::common_type<T, S>::type>>::type;
  template <class T, class S>
  using complex_bool_t = typename std::enable_if<
      std::is_scalar<S>::value && !std::is_same<T, S>::value, bool>::type;

  template <class T, class S>
  complex_broadcast_t<T, S> operator+(std::complex<T> self, S other);
  template <class T, class S>
  complex_broadcast_t<T, S> operator+(S self, std::complex<T> other);
  template <class T, class S>
  complex_broadcast_t<T, S> operator-(std::complex<T> self, S other);
  template <class T, class S>
  complex_broadcast_t<T, S> operator-(S self, std::complex<T> other);
  template <class T, class S>
  complex_broadcast_t<T, S> operator*(std::complex<T> self, S other);
  template <class T, class S>
  complex_broadcast_t<T, S> operator*(S self, std::complex<T> other);
  template <class T, class S>
  complex_broadcast_t<T, S> operator/(std::complex<T> self, S other);
  template <class T, class S>
  complex_broadcast_t<T, S> operator/(S self, std::complex<T> other);

  template <class T, class S>
  complex_bool_t<T, S> operator==(std::complex<T> self, S other);
  template <class T, class S>
  complex_bool_t<T, S> operator==(S self, std::complex<T> other);
  template <class T, class S>
  complex_bool_t<T, S> operator!=(std::complex<T> self, S other);
  template <class T, class S>
  complex_bool_t<T, S> operator!=(S self, std::complex<T> other);

  template <class T, class S>
  bool operator<(std::complex<T> self, std::complex<S> other);
  template <class T, class S>
  bool operator<=(std::complex<T> self, std::complex<S> other);
  template <class T, class S>
  bool operator>(std::complex<T> self, std::complex<S> other);
  template <class T, class S>
  bool operator>=(std::complex<T> self, std::complex<S> other);
  template <class T, class S>
  bool operator&&(std::complex<T> self, std::complex<S> other);
  template <class T, class S>
  bool operator||(std::complex<T> self, std::complex<S> other);

  template <class T>
  bool operator!(std::complex<T> self);

  template <class T>
  struct hash<std::complex<T>> {
    size_t operator()(std::complex<T> const &x) const;
  };
}

PYTHONIC_NS_BEGIN
namespace __builtin__
{
  template <size_t AttributeID, class T>
  T getattr(std::complex<T> const &self);
}
PYTHONIC_NS_END

/* for type inference { */

#include "pythonic/include/types/combined.hpp"
template <class K, class T>
struct __combined<indexable<K>, std::complex<T>> {
  using type = std::complex<T>;
};

template <class K, class T>
struct __combined<std::complex<T>, indexable<K>> {
  using type = std::complex<T>;
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
