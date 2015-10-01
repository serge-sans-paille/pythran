#ifndef PYTHONIC_INCLUDE_TYPES_LONG_HPP
#define PYTHONIC_INCLUDE_TYPES_LONG_HPP

#ifndef USE_GMP
using pythran_long_t = long long;
#define pythran_long(a) pythran_long_t(a)
#else
#include <gmpxx.h>
using pythran_long_t = mpz_class;
#define pythran_long(a) pythran_long_t(#a)

namespace pythonic
{

  /* some math overloads { */

  namespace operator_
  {
    template <class T, class U, class T1>
    auto mod(__gmp_expr<T, U> const &t0, T1 const &t1) -> decltype(t0 % t1);

    template <class T, class U>
    auto floordiv(__gmp_expr<T, U> const &a, long b) -> decltype(a / b);

    template <class T, class U, class Tp, class Up>
    auto floordiv(__gmp_expr<T, U> const &a, __gmp_expr<Tp, Up> const &b)
        -> decltype(a / b);
  }
  /* } */

  template <class T, class U>
  struct gmp_compo;

  template <class T>
  struct gmp_type;

  template <class T, class U>
  struct assignable<__gmp_expr<T, U>> {
    using type = typename gmp_compo<T, U>::type;
    static_assert(!std::is_same<type, double>::value,
                  "Cannot combine long and float.");
  };

  template <class T>
  struct assignable<__gmp_expr<T, T>> {
    using type = typename gmp_type<T>::type;
  };

  template <class T, class U>
  struct lazy<__gmp_expr<T, U>> : assignable<__gmp_expr<T, U>> {
  };

  // GMP_COMPO

  template <class T, class U>
  struct gmp_compo {
    using type = typename gmp_compo<typename gmp_type<T>::type,
                                    typename gmp_type<U>::type>::type;
  };

  template <>
  struct gmp_compo<long, double> {
    using type = double;
  };

  template <>
  struct gmp_compo<double, long> {
    using type = double;
  };

  template <>
  struct gmp_compo<mpz_class, long> {
    using type = mpz_class;
  };

  template <>
  struct gmp_compo<long, mpz_class> {
    using type = mpz_class;
  };

  template <>
  struct gmp_compo<double, mpz_class> {
    using type = double;
  };

  template <>
  struct gmp_compo<mpz_class, double> {
    using type = double;
  };

  template <class T>
  struct gmp_compo<double, T> {
    using type = double;
  };

  template <class T>
  struct gmp_compo<T, double> {
    using type = double;
  };

  template <class T>
  struct gmp_compo<long, T> {
    using type = typename gmp_type<T>::type;
  };

  template <class T>
  struct gmp_compo<T, long> {
    using type = typename gmp_type<T>::type;
  };

  template <class T>
  struct gmp_compo<mpz_class, T> {
    using type = typename gmp_type<T>::type;
  };

  template <class T>
  struct gmp_compo<T, mpz_class> {
    using type = typename gmp_type<T>::type;
  };

  template <class T>
  struct gmp_compo<T, T> {
    using type = typename gmp_type<T>::type;
  };

  template <>
  struct gmp_compo<mpz_class, mpz_class> {
    using type = mpz_class;
  };

  template <>
  struct gmp_compo<long, long> {
    using type = long;
  };

  template <>
  struct gmp_compo<double, double> {
    using type = double;
  };

  // GMP_TYPE

  template <class T>
  struct gmp_type {
    using type = T;
  };

  template <>
  struct gmp_type<__mpz_struct[1]> {
    using type = mpz_class;
  };

  template <class T, class U, class V>
  struct gmp_type<__gmp_binary_expr<T, U, V>> {
    using type = typename gmp_compo<T, U>::type;
  };

  template <class T, class V>
  struct gmp_type<__gmp_unary_expr<T, V>> {
    using type = typename gmp_type<T>::type;
  };

  template <class T, class U, class V>
  struct gmp_type<__gmp_unary_expr<__gmp_expr<T, U>, V>> {
    using type = typename gmp_compo<T, U>::type;
  };

  template <class T, class U>
  struct gmp_type<__gmp_expr<T, U>> {
    using type = typename gmp_compo<T, U>::type;
  };

  template <class T>
  struct gmp_type<__gmp_expr<T, T>> {
    using type = typename gmp_type<T>::type;
  };
}
/* compute hash of a gmp { */
namespace std
{
  template <class T, class U>
  struct hash<__gmp_expr<T, U>> {
    size_t operator()(__gmp_expr<T, U> const &x) const;
  };
}

#include <boost/functional/hash_fwd.hpp>
template <class T, class U>
std::size_t hash_value(__gmp_expr<T, U> const &x);

/* } */
/* type inference stuff  {*/
#include "pythonic/include/types/combined.hpp"

template <>
struct __combined<mpz_class, long int> {
  using type = mpz_class;
};

template <>
struct __combined<long int, mpz_class> {
  using type = mpz_class;
};
/* } */

#ifdef ENABLE_PYTHON_MODULE

namespace pythonic
{

  template <>
  struct from_python<mpz_class> {
    static bool is_convertible(PyObject *obj);
    static mpz_class convert(PyObject *obj);
  };

  template <>
  struct to_python<mpz_class> {
    static PyObject *convert(mpz_class const &v);
  };
}

#endif

#endif

#endif
