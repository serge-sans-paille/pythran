#ifndef PYTHONIC_OPERATOR_IMIN_HPP
#define PYTHONIC_OPERATOR_IMIN_HPP

#include "pythonic/include/operator_/imin.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/numpy/minimum.hpp"

namespace pythonic
{

  namespace operator_
  {

    template <class A, class B>
    auto imin(A const &a, B &&b)
        -> decltype(numpy::functor::minimum{}(a, std::forward<B>(b)))
    {
      return numpy::functor::minimum{}(a, std::forward<B>(b));
    }

    template <class A, class B>
    auto imin(A &a, B &&b)
        -> decltype(a = numpy::functor::minimum{}(a, std::forward<B>(b)))
    {
      return a = numpy::functor::minimum{}(a, std::forward<B>(b));
    }

    DEFINE_FUNCTOR(pythonic::operator_, imin);
  }
}

#endif
