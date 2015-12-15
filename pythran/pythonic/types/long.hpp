#ifndef PYTHONIC_TYPES_LONG_HPP
#define PYTHONIC_TYPES_LONG_HPP

#include "pythonic/include/types/long.hpp"

#ifndef USE_GMP
typedef long long pythran_long_t;
#define pythran_long(a) pythran_long_t(a)
#else
#include <gmpxx.h>
typedef mpz_class pythran_long_t;
#define pythran_long(a) pythran_long_t(#a)

template <class T, class U>
bool operator!(__gmp_expr<T, U> const &t0)
{
  return t0 == 0;
}

namespace pythonic
{

  namespace __builtin__
  {

    long id(pythran_long_t const &t)
    {
      return reinterpret_cast<uintptr_t>(&t);
    }
  }

  /* some math overloads { */

  namespace operator_
  {
    template <class T, class U, class T1>
    auto mod(__gmp_expr<T, U> const &t0, T1 const &t1) -> decltype(t0 % t1)
    {
      return t0 % t1;
    }

    template <class T, class U>
    auto floordiv(__gmp_expr<T, U> const &a, long b) -> decltype(a / b)
    {
      return a / b;
    }

    template <class T, class U, class Tp, class Up>
    auto floordiv(__gmp_expr<T, U> const &a, __gmp_expr<Tp, Up> const &b)
        -> decltype(a / b)
    {
      return a / b;
    }
  }
  /* } */
}
/* compute hash of a gmp { */
namespace std
{
  template <class T, class U>
  size_t hash<__gmp_expr<T, U>>::operator()(__gmp_expr<T, U> const &x) const
  {
    return hash<std::string>()(x.get_str());
  }
}

#include <boost/functional/hash_fwd.hpp>
template <class T, class U>
std::size_t hash_value(__gmp_expr<T, U> const &x)
{
  return std::hash<__gmp_expr<T, U>>()(x);
}

/* } */

#ifdef ENABLE_PYTHON_MODULE

#if PY_MAJOR_VERSION >= 3
#define PyString_AsString PyBytes_AsString
#define PyString_FromString PyBytes_FromString
#endif

namespace pythonic
{

  bool from_python<mpz_class>::is_convertible(PyObject *obj)
  {
    return PyLong_Check(obj);
  }
  mpz_class from_python<mpz_class>::convert(PyObject *obj)
  {
    auto s = PyObject_Str(obj);
    mpz_class r(PyString_AsString(s));
    Py_DECREF(s);
    return r;
  }

  PyObject *to_python<mpz_class>::convert(mpz_class const &v)
  {
    auto s = PyString_FromString(v.get_str().c_str());
    auto l = PyNumber_Long(s);
    Py_DECREF(s);
    return l;
  }
}

#endif

#endif

#endif
