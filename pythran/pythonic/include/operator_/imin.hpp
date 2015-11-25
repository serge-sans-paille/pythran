#ifndef PYTHONIC_INCLUDE_OPERATOR_IMIN_HPP
#define PYTHONIC_INCLUDE_OPERATOR_IMIN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/numpy/minimum.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A, class B>
    auto imin(A const &a, B &&b)
        -> decltype(numpy::functor::minimum{}(a, std::forward<B>(b)));

    template <class A, class B>
    auto imin(A &a, B &&b)
        -> decltype(a = numpy::functor::minimum{}(a, std::forward<B>(b)));

    DECLARE_FUNCTOR(pythonic::operator_, imin);
  }
}

#endif
