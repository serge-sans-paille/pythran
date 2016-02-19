#ifndef PYTHONIC_INCLUDE_NUMPY_AROUND_HPP
#define PYTHONIC_INCLUDE_NUMPY_AROUND_HPP

#include "pythonic/include/numpy/rint.hpp"
#include "pythonic/include/numpy/asarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    // fast path
    template <class E>
    auto around(E const &a) -> decltype(functor::rint{}(a));

    // generic floating point version, pure numpy_expr
    template <class E>
    auto around(E const &a, long decimals) -> typename std::enable_if<
        !std::is_integral<typename types::dtype_of<E>::type>::value,
        decltype(functor::rint{}(
                     a *std::declval<typename types::dtype_of<E>::type>()) /
                 std::declval<typename types::dtype_of<E>::type>())>::type;

    // the integer version is only relevant when decimals < 0
    template <class E>
    auto around(E const &a, long decimals) -> typename std::enable_if<
        std::is_integral<typename types::dtype_of<E>::type>::value,
        decltype((a / std::declval<typename types::dtype_of<E>::type>()) *
                 std::declval<types::dtype_of<E>::type>())>::type;
    // list version
    template <class E>
    auto around(types::list<E> const &a, long decimals)
        -> decltype(around(functor::asarray{}(a), decimals));

    DECLARE_FUNCTOR(pythonic::numpy, around);
  }
}

#endif
