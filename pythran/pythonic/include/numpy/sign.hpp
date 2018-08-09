#ifndef PYTHONIC_INCLUDE_NUMPY_SIGN_HPP
#define PYTHONIC_INCLUDE_NUMPY_SIGN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    double sign(bool const &v)
    {
      return v;
    }

    template <class T>
    double sign(T const &v)
    {
      return v < 0 ? -1. : v == 0 ? 0. : 1.;
    }

    template <class T>
    std::complex<T> sign(std::complex<T> const &v)
    {
      if (v.real())
        return {sign(v.real()), 0};
      else
        return {sign(v.imag()), 0};
    }
  }
#define NUMPY_NARY_FUNC_NAME sign
#define NUMPY_NARY_FUNC_SYM wrapper::sign
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
