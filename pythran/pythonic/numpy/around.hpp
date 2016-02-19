#ifndef PYTHONIC_NUMPY_AROUND_HPP
#define PYTHONIC_NUMPY_AROUND_HPP

#include "pythonic/include/numpy/around.hpp"

#include "pythonic/numpy/rint.hpp"
#include "pythonic/numpy/power.hpp"
#include "pythonic/numpy/asarray.hpp"
#include <nt2/include/functions/pow.hpp>

namespace pythonic
{

  namespace numpy
  {
    // fast path
    template <class E>
    auto around(E const &a) -> decltype(functor::rint{}(a))
    {
      return functor::rint{}(a);
    }

    // generic floating point version, pure numpy_expr
    template <class E>
    auto around(E const &a, long decimals) -> typename std::enable_if<
        !std::is_integral<typename types::dtype_of<E>::type>::value,
        decltype(functor::rint{}(
                     a *std::declval<typename types::dtype_of<E>::type>()) /
                 std::declval<typename types::dtype_of<E>::type>())>::type
    {
      typename types::dtype_of<E>::type const fact = nt2::pow(10., decimals);
      return functor::rint{}(a * fact) / fact;
    }

    // the integer version is only relevant when decimals < 0
    template <class E>
    auto around(E const &a, long decimals) -> typename std::enable_if<
        std::is_integral<typename types::dtype_of<E>::type>::value,
        decltype((a / std::declval<typename types::dtype_of<E>::type>()) *
                 std::declval<typename types::dtype_of<E>::type>())>::type
    {
      typename types::dtype_of<E>::type const fact =
          nt2::pow(10L, std::max(0L, -decimals));
      return (a / fact) * fact;
    }
    // list version
    template <class E>
    auto around(types::list<E> const &a, long decimals)
        -> decltype(around(functor::asarray{}(a), decimals))
    {
      return around(functor::asarray{}(a), decimals);
    }

    DEFINE_FUNCTOR(pythonic::numpy, around);
  }
}

#endif
