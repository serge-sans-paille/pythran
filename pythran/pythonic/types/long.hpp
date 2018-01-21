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

PYTHONIC_NS_BEGIN

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
}
/* } */
PYTHONIC_NS_END

/* compute hash of a gmp { */
namespace std
{
  template <class T, class U>
  size_t hash<__gmp_expr<T, U>>::operator()(__gmp_expr<T, U> const &x) const
  {
    return hash<std::string>()(x.get_str());
  }
}

/* } */

#ifdef ENABLE_PYTHON_MODULE

#if PY_MAJOR_VERSION >= 3
#ifndef PyString_AsString
#define PyString_AsString PyBytes_AsString
#endif
#ifndef PyString_FromString
#define PyString_FromString PyBytes_FromString
#endif
#endif

PYTHONIC_NS_BEGIN

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
PYTHONIC_NS_END

#endif

#endif

#endif
